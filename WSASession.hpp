#pragma once

#include <winsock2.h>

class WSASession
{
public:
	WSASession();
	~WSASession();
private:
	WSADATA *wsaData;
};