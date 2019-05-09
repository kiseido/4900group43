#include "TCPSocket.hpp"


TCPSocket::TCPSocket() 
{
	addrType = IPv4;
	protocol = TCP;
	create();
}


TCPSocket::TCPSocket(int addrType) 
{
	this->addrType = addrType;
	protocol = TCP;
	create();
}


TCPSocket::~TCPSocket() {
	closesocket(sock);
}


void TCPSocket::sendTo(const char * message, SOCKET *clientSock)
{
	if (send(*clientSock, message, strlen(message), 0) < 0)
	{
		std::string error = "\nSend Failed. Error code : " + 
			std::to_string(WSAGetLastError());
		throw TCPException(error);
	}
	puts("Data Sent");
}


int TCPSocket::receiveFrom(SOCKET *otherSocket, const int &buffSize)
{
	int recvSize;
	char * message = new char[buffSize];
	if ((recvSize = recv(*otherSocket, message, buffSize - 1, 0)) == SOCKET_ERROR)
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
