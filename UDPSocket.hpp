#pragma once

#include "Util.hpp";

class UDPSocket 
{
private:
	SOCKET *sock;
	void create();
	int addrType;
public:
	UDPSocket();
	UDPSocket(int addrType);
	~UDPSocket();
};