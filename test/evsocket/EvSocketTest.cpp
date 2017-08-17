#include <stdio.h>
#include <unistd.h>

#include "EvSocket.h"
#include "DataReceiver.h"

#include <pthread.h>
#include <string.h>

#define SEND_PORT 65001
#define RECV_PORT 65002

static volatile bool isClosing = false;

static void
broadcastClose() {
    isClosing = true;
}

static void*
send_routine(void* arg) {
    volatile bool isSending = true;

    EvSocket* sendSocket = new EvSocket(EvSocket::SOCKET_SEND, true);
    sendSocket->create();
    sendSocket->bind(SEND_PORT);
    sendSocket->start();
    char sendBuffer[] = "Sending char";
    while (isSending) {
        sendSocket->send( sizeof(sendBuffer), sendBuffer);
        if (isClosing) {
            sendSocket->stop();
        }
        sleep(1);
    }
    return NULL;
}

static void* 
recv_routine(void* arg) {
    volatile bool isReceiving = true;

    EvSocket* recvSocket = new EvSocket(EvSocket::SOCKET_RECV, true);
    DataReceiver* simpleDataReceiver = new DataReceiver();
    recvSocket->create();
    recvSocket->bind(RECV_PORT);
    recvSocket->addDataReceiveListener(simpleDataReceiver);
    recvSocket->start();

    while (isReceiving) {
        if (simpleDataReceiver->isRequestedClose()) {
            isReceiving = false;

            // request to close other thread
            broadcastClose();
            recvSocket->stop();
        }
        sleep(1);
    }

    return NULL;
}

int 
main(int argc, char* argv[]) {
    pthread_t sendThread;
    pthread_t recvThread;

    int ret;

    if((ret = pthread_create(&sendThread, NULL, &send_routine, NULL)) != 0) {
        printf("[ERR] Failed to create send thread\n");
    }

    if((ret = pthread_create(&recvThread, NULL, &send_routine, NULL)) != 0) {
        printf("[ERR] Failed to create recv thread\n");
    }

    /* Wait for other threads to finish */
    pthread_join(sendThread, NULL);
    pthread_join(recvThread, NULL);

    printf("==== Program Ended! ====\n");
    return 0;
}