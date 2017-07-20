#include <stdio.h>
#include <event.h>
#include <evhttp.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>


typedef struct {
    struct evhttp_connection *conn;
    struct evhttp_request *req;
    bool finished;
} http_client;

void _reqhandler(struct evhttp_request *req, void *state) {
    http_client *hc = (http_client*)state;
    hc->finished = true;

    printf("_reqhandler is called!\n");

    if (req == NULL) {
        printf("req is NULL, exit!\n");
    } else if (req->response_code == 0) {
        printf("connection refused!\n");
    } else if (req->response_code != 200) {
        printf("error: %u %s\n", req->response_code, req->response_code_line);
    } else {
        printf("success: %u %s\n", req->response_code, req->response_code_line);
        char buf[1024];
        int s = 0;
        while ((s = evbuffer_remove(req->input_buffer, &buf, sizeof(buf) - 1)) > 0) {
            buf[s] = '\0';
            printf("%s", buf);
        }
    }
    event_loopexit(NULL);
}

void timeout_cb(int fd, short event, void *arg) {
    http_client *hc = (http_client*)arg;
    printf("Timed out\n");

    if (hc->finished == false){ // Can't cancel request if the callback has already executed
        evhttp_cancel_request(hc->req);
    }
}

void syntax() {
    fprintf(stdout, "Syntax: http-client <ip> <port>\n");
}

int main(int argc, char *argv[]) {
    http_client *hc = (http_client *)malloc(sizeof(http_client));
    hc->finished = false;

    struct event ev;
    struct timeval tv;

    tv.tv_sec = 3; // Timeout is set to 3.005 seconds
    tv.tv_usec = 5000;

    if (argc < 4) {
        syntax();
        return 1;
    }

    const char *addr = argv[1]; //google.com
    unsigned int port = atoi(argv[2]);

    printf("Request to %s %d\n", addr, port);

    event_init();

    hc->conn = evhttp_connection_new(addr, port);
    if (NULL == hc->conn) {
        fprintf(stderr, "Cannot create evhttp_connection\n");
        return 1;
    }
    evhttp_connection_set_timeout(hc->conn, 5);

    hc->req = evhttp_request_new(_reqhandler, (void*)hc);
    if (NULL == hc->req) {
        fprintf(stderr, "Cannot create evhttp_request\n");
        return 1;
    }
    evhttp_add_header(hc->req->output_headers, "Host", addr);
    evhttp_add_header(hc->req->output_headers, "Content-Length", "0");
    // IMPORTANT
    evhttp_make_request(hc->conn, hc->req, EVHTTP_REQ_GET, argv[3]);

    evtimer_set(&ev, timeout_cb, (void*)hc); // Set a timer to cancel the request after certain time
    evtimer_add(&ev, &tv);

    printf("starting event loop..\n");
    printf("\n");
    event_dispatch();

    return 0;
}