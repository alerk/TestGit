#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <evhttp.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/bufferevent.h>

void http_request_done(struct evhttp_request *req, void *arg){
    char buf[1024];
    int s = 0;
    while ((s = evbuffer_remove(req->input_buffer, &buf, sizeof(buf) - 1)) > 0) {
        buf[s] = '\0';
        printf("%s", buf);
    }

    // terminate event_base_dispatch()
    event_base_loopbreak((struct event_base *)arg);
}

void syntax() {
    fprintf(stdout, "Syntax: http-client <ip> <port> <request>\n");
}

int forward_request(const char *addr, unsigned int port, enum evhttp_cmd_type type, const char *uri) {
    struct event_base *base;
    struct evhttp_connection *conn;
    struct evhttp_request *req;

    base = event_base_new();
    conn = evhttp_connection_base_new(base, NULL, addr, port);
    req = evhttp_request_new(http_request_done, base);

    evhttp_add_header(req->output_headers, "Host", "localhost");
    //evhttp_add_header(req->output_headers, "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

    evhttp_make_request(conn, req, type, uri);
    evhttp_connection_set_timeout(req->evcon, 600);
    event_base_dispatch(base);
}

int main(int argc, char **argv){
    struct event_base *base;
    struct evhttp_connection *conn;
    struct evhttp_request *req;

    if (argc < 3) {
        syntax();
        return 1;
    }

    const char *addr = argv[1]; //google.com
    unsigned int port = atoi(argv[2]);
    const char *uri = argv[3];

    for (int i = 1; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);
    }

    forward_request(addr, port, EVHTTP_REQ_GET, uri);

    // base = event_base_new();
    // conn = evhttp_connection_base_new(base, NULL, addr, port);
    // req = evhttp_request_new(http_request_done, base);

    // evhttp_add_header(req->output_headers, "Host", "localhost");
    // //evhttp_add_header(req->output_headers, "Connection", "close");

    // evhttp_make_request(conn, req, EVHTTP_REQ_GET,  "/detectorreading?startPosition=-1&startTimeStamp=1500360300&maxCount=100");
    // evhttp_connection_set_timeout(req->evcon, 600);
    // event_base_dispatch(base);

    return 0;
}