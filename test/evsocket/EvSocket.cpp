#include "EvSocket.h"

#include <unistd.h>
#include <stdio.h>
#include <cstring>

#include <event2/util.h>

#define MAX_LINE 16384
#define TIMEOUT_SEC 3

int clientFd = -1;

/**
 *  Data in from socket
 *  Callback invoke when there is data to be read
 */
void
readcb(struct bufferevent *bev, void *arg) {    
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();
    DataReceiveListener* dataReceiver = evSocket->getDataReceiver();

    struct evbuffer *input;
    char *line;
    size_t n;
    int i;
    input = bufferevent_get_input(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        if (!dataReceiver) {
            continue;
        }
        dataReceiver->onDataReceived(n, line);
        free(line);
    }

    if (evbuffer_get_length(input) >= MAX_LINE) {
        /* Too long; just process what there is and go on so that the buffer
         * doesn't grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            if (!dataReceiver) {
                continue;
            }
            dataReceiver->onDataReceived(n, buf);
        }
    }
}

/**
 * Something is written into buffer: 
 */
void
writecb(struct bufferevent *bev, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();

    struct evbuffer* output;
    int i;
    output = bufferevent_get_output(bev);
    char buf[1024];
    size_t n = evbuffer_get_length(output);

    evbuffer_remove(output, buf, n);

    if ((n = evbuffer_get_length(output)) == 0) {
        // Nothing to write, just quit
        printf("Nothing to write");
    } else {
        printf("%d bytes is written into buffer: %s\n", n, buf);
    }
}

void
errorcb(struct bufferevent *bev, short error, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();
    if (error & BEV_EVENT_EOF) {
        /* connection has been closed, do any clean up here */
        /* ... */
        printf("bufferevent connection closed\n");
    } else if (error & BEV_EVENT_ERROR) {
        /* check errno to see what error occurred */
        /* ... */
        printf("bufferevent error: %d\n", error);
    } else if (error & BEV_EVENT_TIMEOUT) {
        /* must be a timeout event handle, handle it */
        /* ... */
        printf("bufferevent timeout\n");
    }
    bufferevent_free(bev);
}

void 
event_handler(int fd, short event, void *arg) {
    EvSocket *clientSocket = (EvSocket *)arg;
    if (event & EV_TIMEOUT) {
        clientSocket->onTimeout();
    } else if (event & EV_READ) {
        printf("Something to read\n");
    }
}

void 
timeout_cb(int fd, short event, void *arg) {
}

void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
    struct event_base *base = (struct event_base*)user_data;
    struct timeval delay = { 2, 0 };

    printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

    event_base_loopexit(base, &delay);
}

void
do_accept(struct evconnlistener *listener, evutil_socket_t fd, 
    struct sockaddr *address, int socklen, void *ctx) {

    EvSocket* evSocket = static_cast<EvSocket*> (ctx);
    evSocket->createBufferEvent(fd);
}

void
do_connect(struct evconnlistener *listener, evutil_socket_t fd, 
    struct sockaddr *address, int socklen, void *ctx) {
    /* Got a new connection! setup a bufferevent for it */
    struct 
    EvSocket* evSocket = static_cast<EvSocket*> (ctx);
    struct event_base *base = evSocket->getEventBase();
    printf("do_connect() not implemented yet!\n");
}

void 
accept_error_handle(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();

    fprintf(stderr, "Got an error %d (%s) on the listener. Shutting down.\n", 
        err, evutil_socket_error_to_string(err));
    event_base_loopexit(base, NULL);
}

EvSocket::EvSocket() 
    : socketFd(-1) {
}

EvSocket::EvSocket(char direction, bool isServer) 
    : socketFd(-1), direction(direction), server(isServer) {

}

EvSocket::~EvSocket() {

}

// Server initialization
bool 
EvSocket::create(){
    base = event_base_new();
    if (!base)
        return false; /*XXXerr*/

#ifndef WIN32
    {
        int one = 1;
        setsockopt(local_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
    return true;
}

bool
EvSocket::createBufferEvent(evutil_socket_t fd) {
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, readcb, writecb, errorcb, this);

    bufferevent_enable(bev, EV_READ|EV_WRITE);
    return true;
}
bool EvSocket::bind(const int port) {

    if (!server) {
        perror("Not a server");
        return false;
    }
    fprintf(stderr, "Binding to %d\n", port);

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);
    
    setPort(port);

    listener_event = evconnlistener_new_bind(base, do_accept, this,
        LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, 
        (struct sockaddr *)&sin, sizeof(sin));

    if (!listener_event) {
        perror("Couldn't create listener");
        return false;
    }

    evconnlistener_set_error_cb(listener_event, accept_error_handle);
    
    return true;
}

// Client initialization
bool 
EvSocket::connect(const std::string host, const int port) {

    return true;
}

bool 
EvSocket::start() {
    if (!base) {
        return false;
    }
    event_base_dispatch(base); /* Fire the event_base */

    return true;
}

bool 
EvSocket::stop() {
    event_base_loopexit(base, NULL);
    /* Always cleanup */
    if (signal_event) {
        event_free(signal_event);
    }
    if (base) {
        event_base_free(base);
    }
    return true;
}


// Data Transmission
int 
EvSocket::send( int size, const char* sendBuffer ) const {
    if (!(direction && SOCKET_SEND)) {
        fprintf(stderr, "CANNOT SEND\n");
        return -1;
    }
    if (!bev) { // bufferevent is not init
        return -1;
    }
    return bufferevent_write(bev, sendBuffer, size);
    // fprintf(stderr, "TOSEND: %s\n", sendBuffer);
    // return size;
}

size_t 
EvSocket::recv( char* buffer ) const {
    if (!(direction & SOCKET_RECV)) {
        fprintf(stderr, "CANNOT RECEIVE\n");
    }
    return -1;
}

void 
EvSocket::onTimeout() {
    printf("Timeout on port: %d\n", port);
    if (!base) {
        return;
    }
    event_base_loopexit(base, NULL); // If there's no routine, exit, otherwise run until current routines finished
    // Do the clean up
    stop();

}

void EvSocket::addDataReceiveListener(DataReceiveListener* dataListener) {
    this->dataReceiver = dataListener;
}
