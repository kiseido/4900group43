#include <stdio.h>
#include "WSASession.hpp"
#include "Exceptions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "Util.hpp"


void processClient(SOCKET, TCPSocket *);

int main()
{
	puts("TCPServerTest! XD");
	WSASession wsa;
	TCPSocket tSock;
	sockaddr_in sockAddr;
	

	//CHANGE THESE TO WHAT YOU WANT
	const char * addr = LOCAL_HOST;
	int port = 8888;

	tSock.setupSockAddr(&sockAddr, addr, port);

	tSock.bindSock(&sockAddr);

	//MODIFY THIS
	int maxConnectionQueue = 3;

	tSock.listenForConnections(maxConnectionQueue);

	sockaddr_in clientAddr;
	SOCKET newClient;
	while ((newClient = tSock.acceptConnection(&clientAddr)) != INVALID_SOCKET)
	{
		std::thread conThread(*processClient, newClient, &tSock);
		conThread.detach();
	}
}

void processClient(SOCKET s, TCPSocket *tSock)
{
	const char * sendMessage = "Connection successful!";
	char receiveMessage[100];
	tSock->sendTo(sendMessage, &s);
	int result;
	while (true)
	{
		if (tSock->receiveFrom(&s, 100, receiveMessage) == 0)
		{
			std::cout << "User " << s << " has left the chat.";
			tSock->closeSocket(&s);
			break;
		}
		std::cout << "User " << s << ':' << receiveMessage << '\n';
		//tSock->sendTo(receiveMessage, &s);
	}
}