#pragma once

#include "Util.hpp";
#include "Socket.hpp"

class UDPSocket : public Socket
{
private:
	SOCKET *sock;
	void create();
	int addrType;
public:
	Socket * createNew(sockaddr_in *client, SOCKET *s, int addrType);
	UDPSocket();
	UDPSocket(int addrType);
	~UDPSocket();
};