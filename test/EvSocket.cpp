#include "EvSocket.h"

EvSocket::EvSocket() : serverFd(-1) {
}

virtual ~EvSocket::EvSocket() {

}

// Server initialization
bool EvSocket::create(){

}

bool EvSocket::bind() {

}

// Client initialization
bool EvSocket::connect(const std::string host, const int port) {

}

// Data Transmission
int EvSocket::send( const std::string) const {

}

int EvSocket::recv( std::string& ) const {

}
