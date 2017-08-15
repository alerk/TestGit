#include "EvSocket.h"

int main(int argc, char* argv[])
{
    EvSocket* sendSocket = new EvSocket();
    sendSocket->create();
    sendSocket->bind(65001);

    EvSocket* recvSocket = new EvSocket();
    recvSocket->create();
    recvSocket->bind(65002);
    recvSocket->onDataReceived();

    return 0;
}