/*
	Initialize Winsock
*/

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")//Winsock library

int main(int argc, char * argb[]) 
{
	WSADATA wsa;

	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialized.");

	return 0;
}

int initWinsockLibrary() {

}