/*
  A trivial static http webserver using Libevent's evhttp.

  This is not the best code in the world, and it does some fairly stupid stuff
  that you would never want to do in a production webserver. Caveat hackor!

 */

/* Compatibility for possible missing IPv6 declarations */
//#include "../util-internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#endif

#include <evhttp.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#ifdef EVENT__HAVE_NETINET_IN_H
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#endif

#ifdef _WIN32
#ifndef stat
#define stat _stat
#endif
#ifndef fstat
#define fstat _fstat
#endif
#ifndef open
#define open _open
#endif
#ifndef close
#define close _close
#endif
#ifndef O_RDONLY
#define O_RDONLY _O_RDONLY
#endif
#endif

char uri_root[512];

typedef struct {
    struct evhttp_connection *conn;
    struct evhttp_request *req;
    struct evhttp_request *client;
    int response_code;
    struct evbuffer *response_buffer;
    bool finished;
} http_client;

typedef struct {
	char addr[50];
	int port;
} target_address;

void _reqhandler(struct evhttp_request *req, void *state) {
    http_client *hc = (http_client*)state;
    hc->finished = true;

    if (req == NULL) {
        printf("req is NULL, exit!\n");
    } else if (req->response_code == 0) {
        printf("connection refused!\n");
    } else if (req->response_code != 200) {
        printf("_reqhandler error: %u %s\n", req->response_code, req->response_code_line);
        evhttp_send_error(hc->client, req->response_code, req->response_code_line);
    } else {
        printf("_reqhandler success: %u %s\n", req->response_code, req->response_code_line);
        hc->response_buffer = evbuffer_new();

        char buf[1024];
        int s = 0;
        while ((s = evbuffer_remove(req->input_buffer, &buf, sizeof(buf) - 1)) > 0) {
            buf[s] = '\0';
            //printf("%s", buf);
            evbuffer_add(hc->response_buffer, buf, s);
        }
        evhttp_send_reply(hc->client, 200, "OK", hc->response_buffer);
    }
    printf("\n");
    event_loopexit(NULL);
}

void timeout_cb(int fd, short event, void *arg) {
    http_client *hc = (http_client*)arg;
    printf("Timed out\n");

    if (hc->finished == false){ 
    	// Can't cancel request if the callback has already executed
        evhttp_cancel_request(hc->req);
    }
}

int send_request(const char *addr, unsigned int port, enum evhttp_cmd_type type,
	const char *uri,  struct evhttp_request *client) {
    http_client *hc = (http_client *)malloc(sizeof(http_client));
    hc->finished = false;

    struct event ev;
    struct timeval tv;

    tv.tv_sec = 20; // Timeout is set to 20.005 seconds
    tv.tv_usec = 5000;

    printf("Request to %s %d\n", addr, port);

    event_init();

    hc->conn = evhttp_connection_new(addr, port);
    if (NULL == hc->conn) {
        fprintf(stderr, "Cannot create evhttp_connection\n");
        return 1;
    }
    evhttp_connection_set_timeout(hc->conn, 5);
    hc->client = client;

    hc->req = evhttp_request_new(_reqhandler, (void*)hc);
    if (NULL == hc->req) {
        fprintf(stderr, "Cannot create evhttp_request\n");
        return 1;
    }

    evhttp_add_header(hc->req->output_headers, "Host", addr);
    evhttp_add_header(hc->req->output_headers, "Content-Length", "0");
    // IMPORTANT
    evhttp_make_request(hc->conn, hc->req, type, uri);

	// Set a timer to cancel the request after certain time
    evtimer_set(&ev, timeout_cb, (void*)hc); 
    evtimer_add(&ev, &tv);

    printf("starting event loop..\n");
    
    event_dispatch();

    return 0;
}

static void forward_request(struct evhttp_request *req, void *arg) {
	const char *cmdtype;
	struct evkeyvalq *headers;
	struct evkeyval *header;
	struct evbuffer *buf;
	target_address *sx = (target_address*) arg;
	enum evhttp_cmd_type type;
	const char *uri;
	
	printf("forward_request called\n");

	switch (evhttp_request_get_command(req)) {
	case EVHTTP_REQ_GET: cmdtype = "GET"; break;
	case EVHTTP_REQ_POST: cmdtype = "POST"; break;
	case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
	case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
	case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
	case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
	case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
	case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
	case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
	default: cmdtype = "unknown"; break;
	}

	type = evhttp_request_get_command(req);

	printf("\nReceived a %s request for %s\nHeaders:\n",
	    cmdtype, evhttp_request_get_uri(req));

	uri = evhttp_request_get_uri(req);

	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header;
	    header = header->next.tqe_next) {
		printf("  %s: %s\n", header->key, header->value);
	}

	buf = evhttp_request_get_input_buffer(req);
	puts("Input data: <<<");
	while (evbuffer_get_length(buf)) {
		int n;
		char cbuf[128];
		n = evbuffer_remove(buf, cbuf, sizeof(cbuf));
		if (n > 0)
			(void) fwrite(cbuf, 1, n, stdout);
	}
	puts(">>>");

	evhttp_add_header(evhttp_request_get_output_headers(req),
		    "Content-Type", "text/xml");

	send_request(sx->addr, sx->port, type, uri, req);

	
}

static void syntax(void)
{
	fprintf(stdout, "Syntax: proxy-server <sX address> <sX port>\n");
}

int main(int argc, char **argv)
{
	struct event_base *base;
	struct evhttp *http;
	struct evhttp_bound_socket *handle;

	target_address *sx;

	ev_uint16_t port = 8088;
#ifdef _WIN32
	WSADATA WSAData;
	WSAStartup(0x101, &WSAData);
#else
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (1);
#endif
	if (argc < 3) {
		syntax();
		return 1;
	}
	sx = (target_address *)malloc(sizeof(target_address));
	strcpy(sx->addr, argv[1]);
	sx->port = atoi(argv[2]);

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Couldn't create an event_base: exiting\n");
		return 1;
	}

	/* Create a new evhttp object to handle requests. */
	http = evhttp_new(base);
	if (!http) {
		fprintf(stderr, "couldn't create evhttp. Exiting.\n");
		return 1;
	}

	/* We want to accept arbitrary requests, so we need to set a "generic"
	 * cb.  We can also add callbacks for specific paths. */
	evhttp_set_gencb(http, forward_request, (void *)sx);

	/* Now we tell the evhttp what port to listen on */
	handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", port);
	if (!handle) {
		fprintf(stderr, "couldn't bind to port %d. Exiting.\n",
		    (int)port);
		return 1;
	}

	{
		/* Extract and display the address we're listening on. */
		struct sockaddr_storage ss;
		evutil_socket_t fd;
		ev_socklen_t socklen = sizeof(ss);
		char addrbuf[128];
		void *inaddr;
		const char *addr;
		int got_port = -1;
		fd = evhttp_bound_socket_get_fd(handle);
		memset(&ss, 0, sizeof(ss));
		if (getsockname(fd, (struct sockaddr *)&ss, &socklen)) {
			perror("getsockname() failed");
			return 1;
		}
		if (ss.ss_family == AF_INET) {
			got_port = ntohs(((struct sockaddr_in*)&ss)->sin_port);
			inaddr = &((struct sockaddr_in*)&ss)->sin_addr;
		} else if (ss.ss_family == AF_INET6) {
			got_port = ntohs(((struct sockaddr_in6*)&ss)->sin6_port);
			inaddr = &((struct sockaddr_in6*)&ss)->sin6_addr;
		} else {
			fprintf(stderr, "Weird address family %d\n",
			    ss.ss_family);
			return 1;
		}
		addr = evutil_inet_ntop(ss.ss_family, inaddr, addrbuf,
		    sizeof(addrbuf));
		if (addr) {
			printf("Listening on %s:%d\n", addr, got_port);
			evutil_snprintf(uri_root, sizeof(uri_root),
			    "http://%s:%d",addr,got_port);
		} else {
			fprintf(stderr, "evutil_inet_ntop failed\n");
			return 1;
		}
	}

	event_base_dispatch(base);

	return 0;
}
