#include "TCPSocket.hpp"


TCPSocket::TCPSocket() 
{
	addrType = IPv4;
	protocol = TCP;
	sockType = SOCK_STREAM;
	this->create();
}


TCPSocket::TCPSocket(int addrType) 
{
	this->addrType = addrType;
	protocol = TCP;
	sockType = SOCK_STREAM;
	create();
}


TCPSocket::~TCPSocket() {
	closesocket(sock);
}

void TCPSocket::listenForConnections(int maxConQueue)
{
	puts("\nListening...");
	if (listen(sock, maxConQueue) == SOCKET_ERROR)
	{
		error = "\nListen failed with error code : " +
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
}

SOCKET TCPSocket::acceptConnection(struct sockaddr_in *client)
{
	puts("\nAccepting incoming connections...");
	int size = sizeof(struct sockaddr_in);
	SOCKET newSocket = accept(sock, (struct sockaddr *)client, &size);
	if (newSocket == INVALID_SOCKET)
	{
		std::string error = "\nAccept failed with error code: " +
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
	}
	puts("\nConnection accepted");

	return newSocket;
}

void TCPSocket::sendTo(const char * message, SOCKET *s)
{
	if (send(*s, message, strlen(message), 0) < 0)
	{
		std::string error = "\nSend Failed. Error code : " + 
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
	puts("Data Sent");
}


int TCPSocket::receiveFrom(SOCKET *s, const int &buffSize)
{
	int recvSize;
	char * message = new char[buffSize];
	if ((recvSize = recv(*s, message, buffSize - 1, 0)) == SOCKET_ERROR)
	{
		const char * error = "\nReceive Failed. Error code : " + 
			WSAGetLastError();
		puts(error);
		throw TCPException(error);

	}
	puts("Reply Received");

	//Add a NULL terminating character to make it a proper string before printing
	message[recvSize] = '\0';
	
	receivedMessages.push(message);
	
	return recvSize;
}
