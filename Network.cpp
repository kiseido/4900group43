/*
	Initialize Winsock
*/

#include "Network.hpp"
#pragma comment(lib, "ws2_32.lib")//Winsock library

std::mutex recMutex;

//Connect to remote server
//void Network::getIPfromSocket(int *family,struct sockaddr_in *sockAddr, char *ip)
//{
//	inet_ntop(*family, &(sockAddr->sin_addr), ip, INET_ADDRSTRLEN);
//	printf("\nIP: %s", ip);
//}
//
//void Network::getPortFromSocket(int *port, struct sockaddr_in *sockAddr)
//{
//	*port = ntohs(sockAddr->sin_port);
//	printf("\nPort: %d", *port);
//}

//boolean Network::liveServer(SOCKET *s, std::vector<Connection> *connections, std::thread &tServerLoop)
//{
//	puts("Waiting for incoming connections...");
//	tServerLoop = std::thread(serverLoop, s, connections);
//	return 0;
//}

//void Network::serverLoop(SOCKET *s, std::vector<Connection> *connections)
//{
//	SOCKET newSocket = NULL;
//	struct sockaddr_in client;
//	while (newSocket != INVALID_SOCKET) {
//		acceptConnection(s, &newSocket, &client);
//		char message[] = "Hello Client, I have received your connection.";
//		send(&newSocket, message);
//		Connection con = { &client, &newSocket };
//		connections->push_back(con);
//	}
//
//	if (newSocket == INVALID_SOCKET)
//	{
//		printf("Accept failed with error code: %d", WSAGetLastError());
//	}
//}

//boolean Network::receiveMessages(SOCKET *s, std::vector<char*> &receivedMessages, std::thread &tReceiveLoop, int buffSize)
//{
//	tReceiveLoop = std::thread(receiveLoop, s, receivedMessages, buffSize);
//	return 0;
//}

//void Network::receiveLoop(SOCKET *s, std::vector<char*> receivedMessages, int buffSize)
//{
//	int ret = 0;
//	//std::vector<char> vecMessage(buffSize);
//
//	for(int i = 0; ret != 2; i++)
//	{
//		recMutex.lock();
//		receivedMessages.push_back(new char[buffSize]);	
//		recMutex.unlock();
//		ret = receive(s, receivedMessages[i], buffSize);
//	}
//
//}



