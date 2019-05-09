#include "WSASession.hpp"
#include <iostream>
#include "Exceptions.hpp"

WSASession::WSASession()
{
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), wsaData))
	{
		const char * message = 
			"\nInitializing winsock failed. Error code: " +
			WSAGetLastError();
		throw WSAException(message);
		puts(message);
	}
	printf("\nInitialized.");
}
WSASession::~WSASession()
{
	if (WSACleanup() == SOCKET_ERROR)
	{
		const char * message =
			"\nWSACleanup Failed. Error code: " +
			WSAGetLastError();
		throw WSAException(message);
		puts(message);
	}
	puts("\nWSA Cleanup Complete.");
}

