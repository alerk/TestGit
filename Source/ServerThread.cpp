/*
 * ResultServerThread.cpp
 *
 *  Created on: May 9, 2015
 *      Author: quyen
 */

#include "ServerThread.h"
#include "Socket/ServerSocket.h"
#define SERVER_PORT 13579
static void run(void* arg);
ServerThread::ServerThread() {
	// TODO Auto-generated constructor stub

}

ServerThread::~ServerThread() {
	// TODO Auto-generated destructor stub
}

void ServerThread::startServerThread() {
	if( pthread_create(&serverThread,NULL,run,this)!=0)
	{
		std::cout << "Fail to create serverThread" << std::endl;
	}
}

void ServerThread::initServerThread() {
}

void ServerThread::joinServerThread() {
	pthread_join(serverThread, NULL);
}

static void run(void* arg)
{
	ServerThread* obj = (ServerThread*)arg;
	try{

		ServerSocket* listenServer = new ServerSocket(SERVER_PORT);
		while(true)
			{
				ServerSocket sendToSocket;
				listenServer->accept(sendToSocket);
				try{
					char buffer[5];
					buffer[0] = 0xAA;
					buffer[1] = 0x55;
					buffer[2] = buffer[3] = 0x00;
					if(obj->hasFire)
					{
						buffer[4] = 0x01;
					}
					else
					{
						buffer[4] = 0x00;
					}

				}catch(SocketException& e)
				{
					std::cout << "Error while accepting client " << e.description() << std::endl;

				}


			}
	}
	catch(SocketException& e)
	{
		std::cout << "Error while creating server " << e.description() << std::endl;
	}


}

void ServerThread::sendAlarm() {
	pthread_mutex_lock()
	hasFire = true;
}
