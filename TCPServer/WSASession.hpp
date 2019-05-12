#pragma once

#include <winsock2.h>

class WSASession
{
public:
	WSASession();
	~WSASession();
	WSADATA wsaData;
private:

};