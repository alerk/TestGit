/*
  This example program provides a trivial server program that listens for TCP
  connections on port 9995.  When they arrive, it writes a short message to
  each client connection, and closes each connection once it is flushed.

  Where possible, it exits cleanly in response to a SIGINT (ctrl-c).
*/


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 9995;

static void listener_cb(struct evconnlistener *, evutil_socket_t,
    struct sockaddr *, int socklen, void *);
static void conn_writecb(struct bufferevent *, void *);
static void conn_readcb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);
static void signal_cb(evutil_socket_t, short, void *);

int
main(int argc, char **argv)
{
	struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;

	struct sockaddr_in sin;
#ifdef _WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	    (struct sockaddr*)&sin,
	    sizeof(sin));

	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");
	return 0;
}

static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
	
    bufferevent_enable(bev, EV_WRITE | EV_READ);
	// bufferevent_enable(bev, EV_WRITE);
	// bufferevent_disable(bev, EV_READ);

	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

/**
 * Called after something is written to the buffer
 * Callback to invoke when the file descriptor is ready for writing, 
 * or NULL if no callback is desired
 */
static void
conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
    size_t n = evbuffer_get_length(output);
	printf("Something is written into buffer: %d byte\n", n);
    // uint8_t data[1024];
    // int readable = evbuffer_remove(output, data, n);
    // int is_exit = (strncmp("exit", data, 4) == 0);
    // if (!is_exit) 
    // {
    //     printf("Reply to client %d bytes: %s\n", readable, data);
    // }
    // else 
    // {
    //     printf("exit received\n");
    //     bufferevent_free(bev);
    // }
	// if (evbuffer_get_length(output) == 0) {
	// 	printf("flushed answer\n");
	// 	bufferevent_free(bev);
	// }
}

/** 
 * Do the echoing
 * Callback to invoke when there is data to be read, or NULL if no callback is desired
 */
static void
conn_readcb(struct bufferevent *bev, void *user_data)
{
    uint8_t data[1024];
	char* line;
    size_t n;
	struct evbuffer* input = bufferevent_get_input(bev);
	struct evbuffer* output = bufferevent_get_output(bev);
    for(;;)
    {
        line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF);
        if (n <= 0)
        {
            // Done
            break;
        }
		strcpy(data, line);
        printf("read: %s\n", data);
        data[n] = '_';
		data[n+1] = '\0';
		printf("After read, do not add data back to output\n");
		evbuffer_add(output, "Received data\n", 14);
    }
}

static void
conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	} else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
		    strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	 * timeouts */
	bufferevent_free(bev);
}

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}
