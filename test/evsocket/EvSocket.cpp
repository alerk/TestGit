#include "EvSocket.h"
#include <unistd.h>

#define MAX_LINE 16384


int clientFd = -1;

/**
 *  Data in from socket
 *  Callback invoke when there is data to be read
 */
static void
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
        // if (!dataReceiver && (direction & SOCKET_RECV)) {
        if (!dataReceiver) {
            dataReceiver->onDataReceived(n, line);
        }
        printf("Received %s\n", line);
        free(line);
    }

    if (evbuffer_get_length(input) >= MAX_LINE) {
        /* Too long; just process what there is and go on so that the buffer
         * doesn't grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            // if (!dataReceiver && (direction & SOCKET_RECV)) {
            if (!dataReceiver) {
                dataReceiver->onDataReceived(n, buf);
                printf("Received %s\n", line);
            }
        }
    }
}

/**
 * Something is written into buffer: 
 */
static void
writecb(struct bufferevent *bev, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();
    DataReceiveListener* dataReceiver = evSocket->getDataReceiver();

    struct evbuffer *input, *output;
    int i;
    output = bufferevent_get_output(bev);
    char buf[1024];
    size_t n = evbuffer_get_length(output);

    evbuffer_remove(output, buf, n);

    // while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
    //     for (i = 0; i < n; ++i)
    //         line[i] = rot13_char(line[i]);
    //     evbuffer_add(output, line, n);
    //     evbuffer_add(output, "\n", 1);
    //     free(line);
    // }

    // if (evbuffer_get_length(input) >= MAX_LINE) {
    //     /* Too long; just process what there is and go on so that the buffer
    //      * doesn't grow infinitely long. */
    //     char buf[1024];
    //     while (evbuffer_get_length(input)) {
    //         int n = evbuffer_remove(input, buf, sizeof(buf));
    //         for (i = 0; i < n; ++i)
    //             buf[i] = rot13_char(buf[i]);
    //         evbuffer_add(output, buf, n);
    //     }
    //     evbuffer_add(output, "\n", 1);
    // }

    if ((n = evbuffer_get_length(output)) == 0) {
        // Nothing to write, just quit
        printf("Nothing to write");
    } else {
        printf("%d bytes is written into buffer: %s\n", n, buf);
    }
}

static void
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

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
    struct event_base *base = (struct event_base*)user_data;
    struct timeval delay = { 2, 0 };

    printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

    event_base_loopexit(base, &delay);
}

void
do_accept(evutil_socket_t local_socket, short event, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();
    struct bufferevent *bev = evSocket->getBufferEvent();
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    clientFd = accept(local_socket, (struct sockaddr*)&ss, &slen);
    if (clientFd < 0) {
        perror("accept");
    } else if (clientFd > FD_SETSIZE) {
        close(clientFd);
    } else {
        // struct bufferevent *bev;
        evutil_make_socket_nonblocking(clientFd);
        bev = bufferevent_socket_new(base, clientFd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, readcb, writecb, errorcb, (void*)evSocket);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ|EV_WRITE);
    }
}

void
do_connect(evutil_socket_t local_socket, short event, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    struct event_base *base = evSocket->getEventBase();
    printf("do_connect() not implemented yet!\n");
    // struct event_base *base = (struct event_base*) arg;
    // struct sockaddr_storage ss;
    // socklen_t slen = sizeof(ss);
    // int fd = ::connect(local_socket, (struct sockaddr *)&ss, &slen);
    // if (status != 0) {
    //     return false;
    // }
    
    // if (fd < 0) {
    //     perror("accept");
    // } else if (fd > FD_SETSIZE) {
    //     close(fd);
    // } else {
    //     evutil_make_socket_nonblocking(fd);
    //     bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);        
    //     bufferevent_setcb(bev, EvSocket::readcb, NULL, EvSocket::errorcb, NULL);
    //     bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
    //     bufferevent_enable(bev, EV_READ|EV_WRITE);
    // }
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
bool EvSocket::create(){
    base = event_base_new();
    if (!base)
        return false; /*XXXerr*/

    local_socket = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(local_socket);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(local_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
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

    if (::bind(local_socket, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return false;
    }

    if (::listen(local_socket, 16)<0) {
        perror("listen");
        return false;
    }

    listener_event = event_new(base, local_socket, EV_READ|EV_PERSIST, do_accept, (void*) this);
    /*XXX check it */
    event_add(listener_event, NULL);
    /* Create the signal_event */
    // signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

    // if (!signal_event || event_add(signal_event, NULL)<0) {
    //     fprintf(stderr, "Could not create/add a signal event!\n");
    //     return false;
    // }

    return true;
}

bool EvSocket::accept(EvSocket& newSocket) {

    return true;
}

// Client initialization
bool EvSocket::connect(const std::string host, const int port) {
    if (server) {
        perror("Not a client");
        return false;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    int status = inet_pton(AF_INET, host.c_str(), &sin.sin_addr);

    if (errno == EAFNOSUPPORT) {
        return false;
    }

    connect_event = event_new(base, connector, EV_READ|EV_PERSIST, do_connect, (void*)base);
    /*XXX check it */
    event_add(connect_event, NULL);
    /* Create the signal_event */
    // signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

    if (!signal_event || event_add(signal_event, NULL)<0) {
        fprintf(stderr, "Could not create/add a signal event!\n");
        return false;
    }

    return true;
}

bool EvSocket::start() {

    if (!base) {
        return false;
    }
    event_base_dispatch(base); /* Fire the event_base */

    return true;
}

bool EvSocket::stop() {

    struct timeval delay = { 1, 0 };
    event_base_loopexit(base, &delay);
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
int EvSocket::send( int size, const char* sendBuffer ) const {
    if (!(direction && SOCKET_SEND)) {
        return -1;
    }
    if (!bev) { // bufferevent is not init
        return -1;
    }
    // return bufferevent_write(bev, sendBuffer, size);
    fprintf(stderr, "TOSEND: %s\n", sendBuffer);
    return size;
}

size_t EvSocket::recv( char* buffer ) const {
    if (!(direction & SOCKET_RECV)) {
        return -1;
    }
    // uint8_t data[1024];
    // size_t n;
    // size_t total;

    // for (;;) {
    //     if ((n = bufferevent_read(bev, data, sizeof(data)-1)) <= 0) {
    //         printf("No more data\n");
    //         break;
    //     }
    //     total += n;
    //     data[n] = '\0';
    //     printf("Received: %s\n", data);
    //     if (dataReceiver) {
    //         dataReceiver->onDataReceived(n, data);
    //     }
    // }
    // return total;
    return -1;
}

void EvSocket::addDataReceiveListener(DataReceiveListener* dataListener) {
    this->dataReceiver = dataListener;
}
