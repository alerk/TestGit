#ifndef EVSOCKET_H
#define EVSOCKET_H

#include <sys/types.h>
/* For socket functions */
#include <sys/socket.h>
/* For sockaddr_in */
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <arpa/inet.h>

/* For fcntl */
#include <fcntl.h>
/* For signal SIGINT */
#include <signal.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include "DataReceiveListener.h"

class EvSocket {
public:
    static const char SOCKET_SEND = 0x01;
    static const char SOCKET_RECV = 0x02;

    EvSocket();
    EvSocket(char direction, bool isServer);
    virtual ~EvSocket();

    // Server initialization
    bool create();
    bool bind( const int port );
    bool accept(EvSocket& newSocket);

    // Client initialization
    bool connect(const std::string host, const int port);

    // Event start, stop
    bool start();
    bool stop();

    // Data Transmission
    int send(int , const char* ) const;
    size_t recv( char* ) const;

    /* --- Getter and Setter --- */
    // event_base
    struct event_base* getEventBase() {
        return base;
    }

    // local_socket
    evutil_socket_t getLocalSocket() {
        return local_socket;
    }

    // dataReceiver
    DataReceiveListener* getDataReceiver() {
        return dataReceiver;
    }

    // buffer event
    struct bufferevent* getBufferEvent() {
        return bev;
    }

    // virtual void onDataToSend( std::string& ) = 0;
    // virtual void onDataReceived( std::string& ) = 0;

    bool isServer() { return server; }
    bool isValid() { return socketFd != -1; }

    void addDataReceiveListener(DataReceiveListener* listener);

private:
    char direction;
    bool server;

    int socketFd;
    struct sockaddr_in addr;

    // libevent socket
    evutil_socket_t local_socket;
    evutil_socket_t connector;
    struct sockaddr_in sin;
    struct event_base *base;
    struct event *listener_event;
    struct event *connect_event;
    struct event *signal_event;

    struct bufferevent *bev;
    // DataReceiveListener interface
    DataReceiveListener* dataReceiver;

    void readcb(struct bufferevent *bev, void *ctx);
    void writecb(struct bufferevent *bev, void *ctx);
    void errorcb(struct bufferevent *bev, short error, void *ctx);

    // void do_accept(evutil_socket_t listener, short event, void *arg);
    // void do_read(evutil_socket_t fd, short events, void *arg);
    // void do_write(evutil_socket_t fd, short events, void *arg);
};
#endif