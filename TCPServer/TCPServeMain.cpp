#include <stdio.h>
#include "WSASession.hpp"
#include "Exceptions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "Util.hpp"


void processClient(SOCKET, TCPSocket *, int index);

int main()
{
	puts("TCP Server Test! XD");
	WSASession wsa;
	TCPSocket tSock;
	sockaddr_in sockAddr;
	

	//CHANGE THESE TO WHAT YOU WANT
	const char * addr = "142.232.142.251";
	int port = 8888;

	tSock.setupSockAddr(&sockAddr, addr, port);

	tSock.bindSock(&sockAddr);

	//MODIFY THIS TOO
	int maxConnectionQueue = 3;

	tSock.listenForConnections(maxConnectionQueue);

	sockaddr_in clientAddr;
	SOCKET newClient;
	for (int index = 0; (newClient = tSock.acceptConnection(&clientAddr)) != INVALID_SOCKET; index++)
	{
		tSock.clients.push_back(newClient);
		std::thread conThread(*processClient, newClient, &tSock, index);
		conThread.detach();
		int clientPort;
		tSock.getPortFromSockAddr(&clientAddr, &clientPort);
		std::cout << "Client Port: " << port;
	}
}

void processClient(SOCKET s, TCPSocket *tSock, int index)
{
	const char * sendMessage = "Connection successful!";
	char receiveMessage[100];
	tSock->sendTo(sendMessage, &s);
	int result;
	while (true)
	{
		if (tSock->receiveFrom(&s, 100, receiveMessage) == 0)
		{
			tSock->clients.erase(tSock->clients.begin() + index);
			std::cout << "User " << s << " has left the chat.";
			tSock->closeSocket(&s);
			break;
		}
		std::string strRecv(receiveMessage);
		std::string s(std::to_string(s));
		std::string strBuff = "\tUser " + s + ": ";
		strBuff += strRecv;

		const char * endMsg = strBuff.c_str();
		for (int i = 0; i < tSock->clients.size(); i++) {
			tSock->sendTo(endMsg, &tSock->clients[i]);
		}
		std::cout << "User " << s << ": " << receiveMessage << '\n';
	}
}