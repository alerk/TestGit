#ifndef EVSOCKET_H
#define EVSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <arpa/inet.h>

class EvSocket {

public:
    EvSocket();
    virtual ~EvSocket();

    // Server initialization
    bool create();
    bool bind( const int port );

    // Client initialization
    bool connect(const std::string host, const int port);

    // Data Transmission
    int send( const std::string) const;
    int recv( std::string& ) const;

    // virtual void onDataToSend( std::string& ) = 0;
    // virtual void onDataReceived( std::string& ) = 0;

    bool isValid() { return serverFd != -1; }

private:
    int serverFd;
    struct sockaddr_in addr;
}
#endif