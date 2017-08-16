#ifndef EVSOCKET_H
#define EVSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <arpa/inet.h>

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

    // Client initialization
    bool connect(const std::string host, const int port);

    // Event start, stop
    bool start();
    bool stop();

    // Data Transmission
    int send( const char* , int) const;
    int recv( char* ) const;

    // virtual void onDataToSend( std::string& ) = 0;
    // virtual void onDataReceived( std::string& ) = 0;

    bool isServer() { return server; }
    bool isValid() { return serverFd != -1; }

    void addDataReceiveListener(DataReceiveListener* listener);

private:
    int serverFd;
    struct sockaddr_in addr;

    // libevent socket
    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event_base *base;
    struct event *listener_event;
    struct event *signal_event;

    struct bufferevent *bev;
    // DataReceiveListener interface
    DataReceiveListener* dataReceiver;
    
    char direction;
    bool server;

    static void readcb(struct bufferevent *bev, void *ctx);
    static void writecb(struct bufferevent *bev, void *ctx);
    static void errorcb(struct bufferevent *bev, short error, void *ctx);

    static void do_accept(evutil_socket_t listener, short event, void *arg);
    static void do_read(evutil_socket_t fd, short events, void *arg);
    static void do_write(evutil_socket_t fd, short events, void *arg);
}
#endif