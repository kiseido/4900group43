#include "TCPSocket.hpp"

/*
Creates a TCP Socket that defaults to IPv4 address type.
*/
TCPSocket::TCPSocket() 
{
	addrType = IPv4;
	create();
}

TCPSocket::TCPSocket(int addrType) 
{
	addrType = addrType;
	create();
}

TCPSocket::~TCPSocket() {
	closesocket(*sock);
}

void TCPSocket::create()
{
	if ((*sock = socket(addrType, SOCK_STREAM, TCP)) == INVALID_SOCKET) 
	{
		const char * error = "Could not create socket : " + 
			WSAGetLastError();
		throw TCPException(error);
		puts(error);
	}
	printf("\nSocket created.");
}

void TCPSocket::sendTo(const char * message) 
{
	if (send(*sock, message, strlen(message), 0) < 0)
	{
		const char * error = "\nSend Failed. Error code : " + 
			WSAGetLastError();
		throw TCPException(error);
		puts(error);
	}
	puts("Data Sent");
}

int TCPSocket::receiveFrom(std::queue<char*> &receivedMessages, const int &buffSize)
{
	int recvSize;
	char * message = new char[buffSize];
	if ((recvSize = recv(*sock, message, buffSize - 1, 0)) == SOCKET_ERROR)
	{
		const char * error = "\nReceive Failed. Error code : " + 
			WSAGetLastError();
		throw TCPException(error);
		puts(error);
	}
	puts("Reply Received");

	//Add a NULL terminating character to make it a proper string before printing
	message[recvSize] = '\0';
	
	receivedMessages.push(message);
	//if (recvSize == 0)
	//{
	//	msgRcvd = false;
	//	return;
	//}
	//msgRcvd = true;
}
