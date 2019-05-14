#include <stdio.h>
#include "WSASession.hpp"
#include "Exceptions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "Util.hpp"

void processSend(TCPSocket *tSock);

int main()
{
	puts("TCP Client Test! XD");
	WSASession wsa;
	try {
		wsa = WSASession();
	}
	catch (WSAException e) { puts(e.what()); }

	TCPSocket tSock;
	sockaddr_in sockAddr;
	
	//CHANGE THESE TO WHAT YOU WANT
	const char * addr = "142.232.142.251";
	int port = 8887;

	try {
		tSock.setupSockAddr(&sockAddr, addr, port);

		tSock.connectToServer(&sockAddr);

		std::thread thrSend(processSend, &tSock);
		thrSend.detach();

		char receiveMessage[100];
		int result;
		SOCKET * s = tSock.getSock();
		while (true)
		{
			if (tSock.receiveFrom(s, 100, receiveMessage) == 0)
			{
				std::cout << "User " << s << " has left the chat.";
				tSock.closeSocket(s);
				break;
			}
			std::cout << receiveMessage << '\n';
		}
	}
	catch (TCPException e) { puts(e.what()); }

	
}

void processSend(TCPSocket *tSock)
{
	std::string message;
	while (true)
	{
		getline(std::cin, message);
		const char * cMessage = message.c_str();
		tSock->sendTo(cMessage);
	}
}

void processReply(SOCKET s, TCPSocket *tSock)
{
	char receiveMessage[100];
	int result;
	while (true)
	{
		if (tSock->receiveFrom(&s, 100, receiveMessage) == 0)
		{
			std::cout << "User " << s << " has left the chat.";
			tSock->closeSocket(&s);
			break;
		}
		std::cout << receiveMessage;
	}
}