#pragma once
#include "Util.hpp"

class TCPSocket
{
private:
	int addrType;
	SOCKET *sock;
	std::queue<char*> receivedMessages;
	void create();

public:
	TCPSocket();
	TCPSocket(int addrType);
	~TCPSocket();
	void sendTo(const char * message);
	/*
	This receives a message from this socket and stores it in the
	receivedMessages queue if there is a message.
	@return 0 if no messages or otherwise size of messsage in bytes
	@param buffSize is the buffer size in bytes for the message buffer
	*/
	int receiveFrom(const int &buffSize);
};
