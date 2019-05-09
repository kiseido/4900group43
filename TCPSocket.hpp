#pragma once
#include "Util.hpp"
#include "Socket.hpp"

class TCPSocket : public Socket
{
private:

public:

	/*Constructor creates a TCP Socket that defaults to IPv4 
	address type.*/
	TCPSocket();

	/*Constructor creates a TCP Socket and allows you to set 
	the address type.
	@param addrType the addressType you desire(IPv4 or IPv6);*/
	TCPSocket(int addrType);

	/*Destructor closes the socket. */
	~TCPSocket();

	/*	Sends message to bound address & port.
	@param message message to be sent. */
	void sendTo(const char * message, SOCKET *clientSock);

	/*  Receives a message from bound address & port and 
	stores it in the receivedMessages queue if there is 
	a message.
	@param buffSize the max buffer size in bytes for the 
	received message
	@return 0 if connection closed, SOCKET_ERROR if error, 
	or number of bytes received.*/
	int receiveFrom(SOCKET *otherSocket, const int &buffSize);
};
