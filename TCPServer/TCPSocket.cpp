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
	//puts("\nAccepting incoming connections...");
	int size = sizeof(struct sockaddr_in);
	SOCKET newSocket;
	if ((newSocket = accept(sock, (struct sockaddr *)client, &size)) == INVALID_SOCKET)
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
	//puts("\nConnection accepted");
	std::cout << "\nUser " << newSocket << " has joined the chat!\n";
	return newSocket;
}

SOCKET TCPSocket::acceptConnection(SOCKET *sock, struct sockaddr_in *client)
{
	//puts("\nAccepting incoming connections...");
	int size = sizeof(struct sockaddr_in);
	SOCKET newSocket;
	if ((newSocket = accept(*sock, (struct sockaddr *)client, &size)) == INVALID_SOCKET)
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
	std::cout << "\nUser " << newSocket << " has joined the chat!\n";
	return newSocket;
}

void TCPSocket::sendTo(const char * message)
{
	if (send(sock, message, strlen(message), 0) < 0)
	{
		std::string error = "\nSend Failed. Error code : " +
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
	//puts("Data Sent");
}


int TCPSocket::receiveFrom(SOCKET *s, const int &buffSize, char* message)
{
	int recvSize;

	//char * message = new char[buffSize];
	if ((recvSize = recv(*s, message, buffSize - 1, 0)) == SOCKET_ERROR)
	{
		std::string error = "\nReceive Failed. Error code : " +
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
	//puts("Reply Received");

	//Add a NULL terminating character to make it a proper string before printing
	message[recvSize] = '\0';

	return recvSize;
}

void TCPSocket::connectToServer(struct sockaddr_in *server)
{
	puts("\nConnecting...");
	if (connect(sock, (struct sockaddr *)server, sizeof(struct sockaddr_in)) < 0)
	{
		std::string error = "\nConnect Error. Error code : " +
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
	puts("\nConnected");
}
