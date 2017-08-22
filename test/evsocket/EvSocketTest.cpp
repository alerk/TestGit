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
    printf("send_routine\n");
    EvSocket* sendSocket = static_cast<EvSocket*>(arg);

    sendSocket->create();
    sendSocket->bind(SEND_PORT);
    sendSocket->start();
    return NULL;
}

static void* 
recv_routine(void* arg) {
    volatile bool isReceiving = true;
    printf("recv_routine\n");
    EvSocket* recvSocket = static_cast<EvSocket*>(arg);

    DataReceiver* simpleDataReceiver = new DataReceiver();
    recvSocket->create();
    recvSocket->bind(RECV_PORT);
    recvSocket->addDataReceiveListener(simpleDataReceiver);
    recvSocket->start();

    return NULL;
}

void*
gen_routine(void* arg) {
    EvSocket* sendSocket = static_cast<EvSocket*>(arg);

    char sendBuffer[] = "Sending char";
    while (true) {
        printf("gen_routine loop\n");
        int ret = sendSocket->send( sizeof(sendBuffer), sendBuffer);
        if (isClosing) {
            sendSocket->stop();
        }
        if (ret <=0) {
            printf("send_routine error, break out\n");
        }
        sleep(1);
    }
    return NULL;
}

int 
main(int argc, char* argv[]) {
    pthread_t sendThread;
    pthread_t recvThread;
    pthread_t generateDataThread;

    EvSocket* sendSocket = new EvSocket(EvSocket::SOCKET_SEND, true);
    EvSocket* recvSocket = new EvSocket(EvSocket::SOCKET_RECV, true);

    int ret;

    if((ret = pthread_create(&sendThread, NULL, &send_routine, sendSocket)) != 0) {
        printf("[ERR] Failed to create send thread\n");
    }

    if((ret = pthread_create(&recvThread, NULL, &recv_routine, recvSocket)) != 0) {
        printf("[ERR] Failed to create recv thread\n");
    }

    if((ret = pthread_create(&generateDataThread, NULL, &gen_routine, sendSocket)) != 0) {
        printf("[ERR] Failed to create gen thread\n");
    }

    /* Wait for other threads to finish */
    pthread_join(sendThread, NULL);
    pthread_join(recvThread, NULL);
    pthread_join(generateDataThread, NULL);

    printf("==== Program Ended! ====\n");
    return 0;
}