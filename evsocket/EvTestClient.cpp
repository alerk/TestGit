#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "EvSocket.h"
#include "DataReceiver.h"

#include <pthread.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>

#define DATA_PORT 65001
#define CMD_PORT 65002

/* Function Prototype */
static void* recv_routine(void* arg);

/* main function */
int main(void) {
    pthread_t recvThread;
    int ret;

    EvSocket* recvSocket = new EvSocket(EvSocket::SOCKET_RECV, false);
    DataReceiver* simpleDataReceiver = new DataReceiver();
    
    recvSocket->create();
    recvSocket->setNonBlocking(true);
    recvSocket->addDataReceiveListener(simpleDataReceiver);
    
    if((ret = pthread_create(&recvThread, NULL, &recv_routine, recvSocket)) != 0) {
        printf("[ERR] Failed to create recv thread\n");
    }

    pthread_join(recvThread, NULL);
    printf("==== Client Program Ended ====\n");
    return 0;
}

static void* 
recv_routine(void* arg) {
    printf("recv_routine\n");
    EvSocket* recvSocket = static_cast<EvSocket*>(arg);
    bool ret = recvSocket->connect("192.168.128.5", DATA_PORT);
    if (!ret) {
        printf("Error in connect() function\n");
        return NULL;
    }
    printf("Connected successfully to server\n");
    ret = recvSocket->start();

    // Traditional socket
    // sockaddr_in m_addr;
    // int m_sock;
    // m_sock = socket ( AF_INET, SOCK_STREAM, 0 );

    // m_addr.sin_family = AF_INET;
    // m_addr.sin_port = htons(DATA_PORT);

    // int status = inet_pton(AF_INET, "192.168.128.5", &m_addr.sin_addr);
    // if ( errno == EAFNOSUPPORT ) {
    //     return NULL;
    // }

    // status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    // if (status != 0) {
    //     perror("Connect");
    //     return NULL;
    // }
    
    /* Careful for the blocking thing */
    // printf("Set non-blocking\n");
    // int opts;
    // bool b = true;

    // opts = fcntl ( m_sock, F_GETFL );

    // if ( opts < 0 ) {
    //     perror("Set non-blocking");
    //     return NULL;
    // }

    // if ( b ) {
    //     opts = ( opts | O_NONBLOCK );
    // } else {
    //     opts = ( opts & ~O_NONBLOCK );
    // }

    // fcntl ( m_sock, F_SETFL,opts );

    // printf("Prepare for downloading\n");
    // int counter = 0;
    // size_t read = 0;
    // while (true) {
    //     char buf[1024 + 1];
    //     memset(buf, 0, sizeof(buf));
    //     if (counter == 0) {
    //         usleep(1000);
    //     }
    //     read = ::recv(m_sock, buf, sizeof(buf) - 1, 0);
    //     if (read > 0) {
    //         buf[read] = '\0';
    //         printf("%5d-Recv: (%d, %s)\n", counter++, read, buf);
    //     }

    //     if (counter == 50) {
    //         break;
    //     }
    // }

    return NULL;
}