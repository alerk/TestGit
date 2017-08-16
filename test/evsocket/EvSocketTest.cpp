#include <stdio.h>

#include "EvSocket.h"
#include "DataReceiver.h"

#include <pthread.h>

#define SEND_PORT 65001
#define RECV_PORT 65002

volatile bool closing = false;

void
broadcastClose() {
    closing = true;
}

static void*
send_routine(void* arg) {
    volatile bool isSending = true;

    EvSocket* sendSocket = new EvSocket();
    sendSocket->create();
    sendSocket->bind(SEND_PORT);
    char sendBuffer[100];
    strcpy(sendBuffer, "Sending char");
    while (isSending) {
        sendSocket->send(sendBuffer, sizeof(sendBuffer));
        if (isClosing) {
            sendSocket->stop();
        }
        sleep(1);
    }
    pthread_join(NULL);
    return NULL;
}

static void* 
recv_routine(void* arg) {
    volatile bool isReceiving = true;

    EvSocket* recvSocket = new EvSocket();
    DataReceiver* simpleDataReceiver = new DataReceiver();
    recvSocket->create();
    recvSocket->bind(RECV_PORT);
    recvSocket->addDataReceiveListener(simpleDataReceiver);

    while (isReceiving) {
        if (simpleDataReceiver->isRequestedClose()) {
            isReceiving = false;

            // request to close other thread
            broadcastClose();
            recvSocket->stop();
        }
    }

    pthread_join(NULL);
    return NULL;
}

int 
main(int argc, char* argv[]) {
    pthread_t sendThread;
    pthread_t recvThread;

    if((ret = pthread_create(&sendThread, NULL, &send_routine, NULL)) <= 0) {
        printf("[ERR] Failed to create send thread\n");
    }

    if((ret = pthread_create(&recvThread, NULL, &send_routine, NULL)) <= 0) {
        printf("[ERR] Failed to create recv thread\n");
    }


    printf("==== Program Ended! ====\n");
    return 0;
}