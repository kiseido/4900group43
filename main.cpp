// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <Ws2tcpip.h>
#include "Network.hpp"

//#include <GL/glew.h>



int main()
{
	printf_s("Hello");
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	//Message to send, this requests the HTML page
	//const char* message = "GET / HTTP/1.1\r\n\r\n";

	initWinsockLibrary(&wsa);
	createSocket(&s);

	//Test for getIPFromDomain
	//char hostName[] = "www.google.ca";
	//char hostName[] = "www.digitalprojects.info";
	//WCHAR ip[100];

	//getIPFromDomain(hostName, ip);

	//Google address
	//const char* addr = "172.217.14.195";
	//int family = AF_INET;
	//int port = 80;

	//setupServer(&server, addr, family, port);
	//connectToServer(&s, &server);
	//sendData(&s, message);
	
	//char server_reply[2000];
	//receiveReply(&s, server_reply);

	////Display the reply
	//puts(server_reply);

	//Test BindSocket
	//Server Info
	//const char* addr = "192.168.1.64";
	SOCKET newSocket;
	struct sockaddr_in client;
	const char* addr = "127.0.0.1";

	int family = AF_INET;
	int port = htons(8888);

	setupServer(&server, addr, family, port);

	bindSocket(&server, &s);

	listenforConnections(&s, 3);

	acceptConnection(&s, &newSocket, &client);

	closeAndCleanup(&s);

	//Prevents console from closing
	getchar();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
