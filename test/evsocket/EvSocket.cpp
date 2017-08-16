#include "EvSocket.h"
/**
 *  Data in from socket
 */
void
EvSocket::readcb(struct bufferevent *bev, void *ctx)
{
    struct evbuffer *input, *output;
    char *line;
    size_t n;
    int i;
    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        for (i = 0; i < n; ++i)
            line[i] = rot13_char(line[i]);
        evbuffer_add(output, line, n);
        evbuffer_add(output, "\n", 1);
        free(line);
    }

    if (evbuffer_get_length(input) >= MAX_LINE) {
        /* Too long; just process what there is and go on so that the buffer
         * doesn't grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            for (i = 0; i < n; ++i)
                buf[i] = rot13_char(buf[i]);
            evbuffer_add(output, buf, n);
        }
        evbuffer_add(output, "\n", 1);
    }
}

/**
 * Something is written into buffer: 
 */
void
EvSocket::writecb(struct bufferevent *bev, void *ctx) {
    struct evbuffer *input, *output;
    char *line;
    size_t n;
    int i;
    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        for (i = 0; i < n; ++i)
            line[i] = rot13_char(line[i]);
        evbuffer_add(output, line, n);
        evbuffer_add(output, "\n", 1);
        free(line);
    }

    if (evbuffer_get_length(input) >= MAX_LINE) {
        /* Too long; just process what there is and go on so that the buffer
         * doesn't grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            for (i = 0; i < n; ++i)
                buf[i] = rot13_char(buf[i]);
            evbuffer_add(output, buf, n);
        }
        evbuffer_add(output, "\n", 1);
    }

    if (evbuffer_get_length(output) == 0) {
        // Nothing to write, just quit
        printf("Nothing to write");
        return;
    }
}

void
EvSocket::errorcb(struct bufferevent *bev, short error, void *ctx)
{
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
EvSocket::do_accept(evutil_socket_t listener, short event, void *arg)
{
    struct event_base *base = (struct event_base*) arg;
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr*)&ss, &slen);
    if (fd < 0) {
        perror("accept");
    } else if (fd > FD_SETSIZE) {
        close(fd);
    } else {
        evutil_make_socket_nonblocking(fd);
        bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, EvSocket::readcb, EvSocket::write, EvSocket::errorcb, NULL);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ|EV_WRITE);
    }
}

void
EvSocket::signal_cb(evutil_socket_t sig, short events, void *user_data)
{
    struct event_base *base = (struct event_base*)user_data;
    struct timeval delay = { 2, 0 };

    printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

    event_base_loopexit(base, &delay);
}

EvSocket::EvSocket() 
    : serverFd(-1) {
}

EvSocket::EvSocket(char direction, bool isServer) 
    : serverFd(-1), direction(direction), server(isServer) {
}

virtual ~EvSocket::EvSocket() {
}

// Server initialization
bool EvSocket::create(){
    base = event_base_new();
    if (!base)
        return; /*XXXerr*/

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

}

bool EvSocket::bind(const int port) {

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return false;
    }

    if (listen(listener, 16)<0) {
        perror("listen");
        return false;
    }

    listener_event = event_new(base, listener, EV_READ|EV_PERSIST, do_accept, (void*)base);
    /*XXX check it */
    event_add(listener_event, NULL);
    /* Create the signal_event */
    signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

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

// Client initialization
bool EvSocket::connect(const std::string host, const int port) {

}

// Data Transmission
int EvSocket::send( const char* sendBuffer, int size) const {
    if (!(direction && SOCKET_SEND)) {
        return -1;
    }
    if (!bev) { // bufferevent is not init
        return -1;
    }
    return bufferevent_write(bev, sendBuffer, size);
}

size_t EvSocket::recv( char* buffer ) const {
    if (!(direction && SOCKET_RECV)) {
        return -1;
    }
    uint8_t data[1024];
    size_t n;
    size_t total;

    for (;;) {
        if ((n = bufferevent_read(bev, data, sizeof(data)-1)) <= 0) {
            printf("No more data\n");
            break;
        }
        total += n;
        data[n] = '\0';
        printf("Received: %s\n", data);
        if (dataReceiver) {
            dataReceiver->onDataReceived(n, data);
        }
    }
    return total;
}

void EvSocket::addDataReceiveListener(DataReceiveListener* listener) {
    dataReceiver = listener;
}
