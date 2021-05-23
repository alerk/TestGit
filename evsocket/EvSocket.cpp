#include "EvSocket.h"

#include <unistd.h>
#include <stdio.h>
#include <cstring>

#include <event2/util.h>

#include <sys/socket.h>
#include <netinet/tcp.h>

#define MAX_LINE 16384
#define TIMEOUT_SEC 3

int clientFd = -1;

void 
set_tcp_no_delay(evutil_socket_t fd) {
    int one = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof one);
}
/**
 *  Data in from socket
 *  Callback invoke when there is data to be read
 */
void
readcb(struct bufferevent *bev, void *arg) {    
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    // struct event_base *base = evSocket->getEventBase();
    DataReceiveListener* dataReceiver = evSocket->getDataReceiver();

    struct evbuffer *input;
    char *line;
    char buf[1024];
    int i;
    input = bufferevent_get_input(bev);
    size_t n = evbuffer_get_length(input);
    if (0 == n) {
        printf("Nothing in the input buffer\n");
    } else {
        evbuffer_remove(input, buf, n);
        evSocket->onDataRead(n, buf);
    }
}

/**
 * Something is written into buffer: 
 */
void
writecb(struct bufferevent *bev, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    // struct event_base *base = evSocket->getEventBase();
    struct evbuffer* output = bufferevent_get_output(bev);
    char buf[1024];
    size_t n = evbuffer_get_length(output);
    if (n == 0) {
        // Nothing to write, just quit
        // printf("Nothing to write");
    } else {
        evbuffer_copyout(output, buf, n);
        evSocket->onDataWrite(n, buf);
    }
}

void
errorcb(struct bufferevent *bev, short error, void *arg) {
    EvSocket* evSocket = static_cast<EvSocket*> (arg);
    // struct event_base *base = evSocket->getEventBase();
    if (error & BEV_EVENT_EOF) {
        /* connection has been closed, do any clean up here */
        /* ... */
        printf("bufferevent connection closed\n");
        evSocket->setClientConnected(0);
        bufferevent_free(bev);
    } else if (error & BEV_EVENT_ERROR) {
        /* check errno to see what error occurred */
        /* ... */
        printf("bufferevent error: %d\n", error);
        evSocket->setClientConnected(0);
        bufferevent_free(bev);
    } else if (error & BEV_EVENT_TIMEOUT) {
        /* must be a timeout event handle, handle it */
        /* ... */
        printf("bufferevent timeout\n");
        evSocket->setClientConnected(0);
        bufferevent_free(bev);
    } else if (error & BEV_EVENT_CONNECTED) {
        /* We're connected to socket. Start reading or writing. */
        /* This event happens only with client socket */
        printf("bufferevent connected to ");
        if (!evSocket->isServer()) {
            evutil_socket_t fd = bufferevent_getfd(bev);
            printf("server: %d\n", fd);
            set_tcp_no_delay(fd);
            sleep(1);
        } else {
            printf("client\n");
            evSocket->setClientConnected(1);
        }
    }
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
    if (evSocket->isClientConnected()) {
        return;
    }
    evSocket->createBufferEvent(fd);
    evSocket->setClientConnected(1);
    printf("do_accept() on %d called!\n", evSocket->getPort());
    // ((struct sockaddr_in*)address)->sin_port);
}

// void
// do_connect(struct evconnlistener *listener, evutil_socket_t fd, 
//     struct sockaddr *address, int socklen, void *ctx) {

//     EvSocket* evSocket = static_cast<EvSocket*> (ctx);
//     evSocket->createBufferEvent(fd);
//     printf("do_connect() called!\n");
// }

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
    : socketFd(-1), direction(direction), server(isServer), clientConnected(0) {

}

EvSocket::~EvSocket() {
    // stop();
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
    int block_size = 50;
    // char *message = (char*) malloc(block_size);
    char *message = (char*) valloc(block_size); // Clang
    sin.sin_family = AF_INET;
    int status = inet_pton(AF_INET, host.c_str(), &(sin.sin_addr));
    sin.sin_port = htons(port);
    if ( errno == EAFNOSUPPORT ) return false;

    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    for (int i=0; i < block_size; i++) {
        message[i] = i;
    }
    bufferevent_setcb(bev, readcb, writecb, errorcb, this);
    bufferevent_enable(bev, EV_READ|EV_WRITE);
    // evbuffer_add(bufferevent_get_output(bev), message, block_size);

    if (bufferevent_socket_connect(bev, 
        (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        /* Error starting connection */
        perror("bufferevent_socket_connect:");
        bufferevent_free(bev);
        return false;
    }
    return true;

    // status = ::connect( socketFd, (struct sockaddr *)&sin, sizeof(sin));    
    // if (status != 0) {
    //     return false;
    // }
    // printf("connect() call createBufferEvent\n");
    // return createBufferEvent(socketFd);
}

bool 
EvSocket::start() {
    if (!base) {
        return false;
    }
    event_base_dispatch(base); /* Fire the event_base */

    /* stop() called but cleanup where the event_base_dispatch() */
    /* Always cleanup */
    if (signal_event) {
        event_free(signal_event);
    }
    if (base) {
        event_base_free(base);
    }
    return true;
}

bool 
EvSocket::stop() {
    // Listen event for server
    if (listener_event) {
        evconnlistener_free(listener_event);
    }

    // buffer event for server and client
    if (bev) {
        bufferevent_free(bev);
    }

    // event_base_loopexit(base, NULL); // bev_exit_on_free
    return true;
}

/* Passively write */
void 
EvSocket::onDataWrite(size_t n, char* buf) {
    printf("%zu bytes is written into buffer: %s\n", n, buf);
}

/* Passively read */
void 
EvSocket::onDataRead(size_t n, char* buf) {
    if (!dataReceiver) {
        return;
    }
    dataReceiver->onDataReceived(n, buf);
}

// Data Transmission
/* Actively write */
int 
EvSocket::send( int size, const char* sendBuffer ) const {
    // if (!(direction && SOCKET_SEND)) {
    if (!(direction & SOCKET_SEND)) { // Clang
        fprintf(stderr, "CANNOT SEND\n");
        return -1;
    }
    if (!bev) { // bufferevent is not init
        return -1;
    }
    if (!clientConnected) {
        return -1;
    }
    // fprintf(stderr, "TOSEND: %s\n", sendBuffer);
    struct evbuffer* output = bufferevent_get_output(bev);
    return evbuffer_add(output, sendBuffer, size);
}

/* Actively read */
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
    // Do the clean up
    stop();

}

void 
EvSocket::addDataReceiveListener(DataReceiveListener* dataListener) {
    this->dataReceiver = dataListener;
}

bool
EvSocket::isRequestedClose() {
    if (server && dataReceiver) {
        return dataReceiver->isRequestedClose();
    }
    return false;
}

void 
EvSocket::setNonBlocking ( const bool b ){

    int opts;

    opts = fcntl(socketFd, F_GETFL);

    if (opts < 0) {
        return;
    }

    if (b) {
        opts = (opts | O_NONBLOCK);
    } else {
        opts = (opts & ~O_NONBLOCK);
    }

    fcntl(socketFd, F_SETFL, opts);
}

