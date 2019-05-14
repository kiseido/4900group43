// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include "Network.hpp"
#include "Util.hpp"
#include "WSASession.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"
//#include <GL/glew.h>

int main()
{
	//TCP Test
	WSASession *wsa;
	struct sockaddr_in sockAddr;

	try {
		wsa = new WSASession();
	}
	catch (WSAException e) { puts(e.what()); }
	try {
		TCPSocket tSock(IPv4);
		char fetchedIP[100];
		char google[] = "www.google.ca";
				
		tSock.getIPFromDomain(google, fetchedIP);
		tSock.setupSockAddr(&sockAddr, fetchedIP, 80);
		tSock.connectToServer(&sockAddr);
		
		const char * message = "A\n";
		
		tSock.sendTo(message, tSock.getSock());
		tSock.receiveFrom(tSock.getSock(), 5000);

		std::cout << tSock.receivedMessages.front();



		//tSock.bindSock(&sockAddr);
		//tSock.listenForConnections(2);
		//SOCKET clientSock = tSock.acceptConnection(&sockAddr);
		//Connection clientCon = { &sockAddr, &clientSock };
		//tSock.sendTo("Hello new connection", clientCon.sock);
		//tSock.receiveFrom(&clientSock, 100);
	}
	catch (TCPException e) { puts(e.what()); }
	


	////UDP Test
	//WSASession *wsa;
	//struct sockaddr_in server, sockAddr;

	//try {
	//	wsa = new WSASession();
	//}
	//catch (WSAException e) { puts(e.what()); }
	//try {
	//	UDPSocket uSock(IPv4);
	//	uSock.setupSockAddr(&server, LOCAL_HOST, 8888);
	//	uSock.bindSock(&server);
	//	
	//	SOCKET s = uSock.getSocket();

	//	puts("\nWaiting for data");
	//	while (true)
	//	{
	//		char buff[100];
	//		int buffLen = sizeof(buff);
	//		
	//		uSock.receiveFrom(&s, buff, buffLen, &sockAddr);

	//		printf("Received packet from %d\n",
	//			ntohs(sockAddr.sin_port));
	//		printf("Data: %s", buff);

	//		puts("Sending Reply");

	//		buffLen = sizeof(buff);
	//		uSock.sendTo(&s, buff, buffLen, &sockAddr);
	//	}
	//	uSock.~UDPSocket();
	//}
	//catch (UDPException e) { puts(e.what()); }
	//WSASession wsa;
	//TCPSocket tSock;

	////Test for getIPFromDomain
	////char hostName[] = "www.google.ca";
	//char hostName[] = "www.digitalprojects.info";
	//char ip[100];
	//
	//tSock.getIPFromDomain(hostName, ip);

	//tSock.getIPFromDomain(hostName, ip);

	//Google address
	//const char* addr = "172.217.14.195";
	//int family = AF_INET;
	//int port = 80;

	//setupServer(&server, addr, family, port);
	//connectToServer(&s, &server);
	//sendData(&s, message);
	//
	//char server_reply[2000];
	//receiveReply(&s, server_reply);

	////Display the reply
	//puts(server_reply);

	//Test BindSocket
	//Server Info
	//const char* addr = "192.168.1.64";
	
	//{
	//	SOCKET newSocket;
	//	struct sockaddr_in client;
	//	const char* addr = LOCAL_HOST;

	//	int family = IPv4;
	//	int port = 8888;
	//	std::vector<Connection> connections;
	//	std::vector<char*> messages;
	//	setupServer(&server, addr, family, port);
	//	bindSocket(&server, &s);
	//	listenforConnections(&s, MAX_BACKLOG);

	//	std::thread tServerLoop;
	//	std::thread tMessageLoop;

	//	liveServer(&s, &connections, tServerLoop);

	//	while (true)
	//	{
	//		if (connections.size() > 0)
	//		{
	//			receiveMessages(connections[0].socket, messages, tMessageLoop, 2000);
	//			break;
	//		}
	//	}

	//	getchar();
	//}
	
	
	//acceptConnection(&s, &newSocket, &client);

	//char message[50] = "Hello Client! I have received your connection";
	//reply(&newSocket, message);

	//char ip[INET_ADDRSTRLEN];
	//int resPort;

	//getSockAddrInfo(ip, &resPort, &client, family);
	
	//closeAndCleanup(&s);

	//Prevents console from closing
	//getchar();
}





