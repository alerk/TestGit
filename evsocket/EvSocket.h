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
#include <event2/listener.h>

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
    bool createBufferEvent(evutil_socket_t fd);
    bool bind( const int port );

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

    // get/set for port
    int getPort() {return port; }
    void setPort(int port) {this->port = port; }

    // get/set for clientConnected
    int isClientConnected() { return clientConnected; }
    void setClientConnected(int connect) { this->clientConnected = connect; }

    // requested close
    bool isRequestedClose();

    // get/set for direction
    char getDirection() { return this->direction; }

    void setNonBlocking ( const bool b );

    // virtual void onDataToSend( std::string& ) = 0;
    // virtual void onDataReceived( std::string& ) = 0;

    bool isServer() { return server; }
    bool isValid() { return socketFd != -1; }

    void addDataReceiveListener(DataReceiveListener* listener);

    void onTimeout();

    void onDataWrite(size_t n, char* buf);
    void onDataRead(size_t n, char* buf);

private:
    char direction;
    bool server;

    int socketFd;
    struct sockaddr_in addr;
    int port;

    // libevent socket
    evutil_socket_t local_socket;
    evutil_socket_t connector;
    struct sockaddr_in sin;
    struct event_base *base;
    struct evconnlistener *listener_event;
    struct event *connect_event;
    struct event *signal_event;

    struct bufferevent *bev;
    // DataReceiveListener interface
    DataReceiveListener* dataReceiver;

    int clientConnected;

    // void readcb(struct bufferevent *bev, void *ctx);
    // void writecb(struct bufferevent *bev, void *ctx);
    // void errorcb(struct bufferevent *bev, short error, void *ctx);

    // void do_accept(evutil_socket_t listener, short event, void *arg);
    // void do_read(evutil_socket_t fd, short events, void *arg);
    // void do_write(evutil_socket_t fd, short events, void *arg);
};
#endif