/*
	Initialize Winsock
*/

#include "Network.hpp"
#include "Util.hpp"
#pragma comment(lib, "ws2_32.lib")//Winsock library

std::mutex recMutex;

//Initialize Winsock
//boolean initWinsockLibrary(WSADATA *wsa)
//{
//	printf("\nInitializing Winsock...");
//	if (WSAStartup(MAKEWORD(2, 2), wsa))
//	{
//		printf("Failed. Error Code : %d", WSAGetLastError());
//		return 1;
//	}
//	printf("\nInitialized.");
//	return 0;
//}

boolean bindSocket(struct sockaddr_in *server, SOCKET *s) {
	//Bind
	if (bind(*s, (struct sockaddr *)server, sizeof(*server)) == SOCKET_ERROR)
	{
		printf("\nBind failed with error code : %d", WSAGetLastError());
		return 1;
	}

	puts("\nBind done!");

	return 0;

}

boolean listenforConnections(SOCKET *s, int maxConQueue)
{
	if (listen(*s, maxConQueue) == SOCKET_ERROR)
	{
		printf("\nListen failed with error code: %d", WSAGetLastError());
		return 1;
	}
	return 0;

}

boolean acceptConnection(SOCKET *s, SOCKET *newSocket, struct sockaddr_in *client) 
{
	puts("\nWaiting for incoming connections...");
	if (accept(s, newSocket, client) == 1) {
		return 1;
	}
	return 0;
}

boolean liveServer(SOCKET *s, std::vector<Connection> *connections, std::thread &tServerLoop)
{
	puts("Waiting for incoming connections...");
	tServerLoop = std::thread(serverLoop, s, connections);
	return 0;
}

void serverLoop(SOCKET *s, std::vector<Connection> *connections)
{
	SOCKET newSocket = NULL;
	struct sockaddr_in client;
	while (newSocket != INVALID_SOCKET) {
		accept(s, &newSocket, &client);
		char message[] = "Hello Client, I have received your connection.";
		send(&newSocket, message);
		Connection con = { &client, &newSocket };
		connections->push_back(con);
	}

	if (newSocket == INVALID_SOCKET)
	{
		printf("Accept failed with error code: %d", WSAGetLastError());
	}
}

boolean accept(SOCKET *s, SOCKET *newSocket, struct sockaddr_in *client)
{
	int size = sizeof(struct sockaddr_in);
	*newSocket = accept(*s, (struct sockaddr *)client, &size);
	if (*newSocket == INVALID_SOCKET)
	{
		printf("\nAccept failed with error code: %d", WSAGetLastError());
		return 1;
	}

	puts("\nConnection accepted");

	return 0;
}

boolean setupServer(struct sockaddr_in *server, const char* addr, int family, int port)
{
	//server->sin_addr.s_addr = inet_addr(addr);
	
	int result = inet_pton(family, addr, &server->sin_addr.s_addr);
	if (result == 0)
	{
		printf("\nSetup Server Failed. Invalid IPv4 or IPv6 string.");
		return 1;
	}
	else if (result == -1)
	{
		printf("\nSetup Server Failed. Error code: %d", WSAGetLastError());
		return 1;
	}
	server->sin_family = family;
	
	
	server->sin_port = htons(port);

	return 0;
}

//Create a socket
//boolean createSocket(SOCKET *s, int protocol) 
//{
//	//Address Family : AF_INET(this is IP version 4)
//	//Type : SOCK_STREAM(this means connection oriented TCP protocol)
//	//Protocol : AUTO(0)[or IPPROTO_TCP, IPPROTO_UDP]
//	int type = protocol == TCP ? SOCK_STREAM : SOCK_DGRAM;
//
//	if ((*s = socket(IPv4, type, protocol)) == INVALID_SOCKET) {
//		printf("Could not create socket : %d", WSAGetLastError());
//		return 1;
//	}
//
//	printf("\nSocket created.");
//	return 0;
//}

//Connect to remote server
boolean connectToServer(SOCKET *s, struct sockaddr_in *server)
{
	if (connect(*s, (struct sockaddr *)server, sizeof(struct sockaddr_in)) < 0)
	{
		puts("\nConnect Error");
		return 1;
	}

	puts("\nConnected");

	return 0;
}

//boolean send(SOCKET *s, char* message)
//{
//	if (send(*s, message, strlen(message), 0) < 0)
//	{
//		printf("\nSend Failed. Error code: %d", WSAGetLastError());
//		return 1;
//	}
//	puts("Data Sent");
//}

boolean receiveMessages(SOCKET *s, std::vector<char*> &receivedMessages, std::thread &tReceiveLoop, int buffSize)
{
	tReceiveLoop = std::thread(receiveLoop, s, receivedMessages, buffSize);
	return 0;
}

void receiveLoop(SOCKET *s, std::vector<char*> receivedMessages, int buffSize) 
{
	int ret = 0;
	//std::vector<char> vecMessage(buffSize);

	for(int i = 0; ret != 2; i++)
	{
		recMutex.lock();
		receivedMessages.push_back(new char[buffSize]);	
		recMutex.unlock();
		ret = receive(s, receivedMessages[i], buffSize);
	}

}

boolean receive(SOCKET *s, char* receivedMessage, int buffSize)
{
	int recv_size;

	if ((recv_size = recv(*s, receivedMessage, buffSize - 1, 0)) == SOCKET_ERROR)
	{
		printf("Receive Failed. Error code %d", WSAGetLastError());
		return 1;
	}

	puts("Reply Received");
	
	//Add a NULL terminating character to make it a proper string before printing
	receivedMessage[recv_size] = '\0';
	if (recv_size == 0) 
	{
		return 2;
	}
	return 0;
}

boolean closeSocket(SOCKET *s) {
	if (closesocket(*s) == SOCKET_ERROR)
	{
		printf("Close Socket Failed. Error code: %d", WSAGetLastError());
		return 1;
	}
}

//boolean cleanupWSA()
//{
//	if (WSACleanup() == SOCKET_ERROR)
//	{
//		printf("WSACleanup Failed. Error code: %d", WSAGetLastError());
//		return 1;
//	}
//
//	return 0;
//}

//boolean closeAndCleanup(SOCKET *s)
//{
//	if (closeSocket(s) == 1 || cleanupWSA() == 1) {
//		return 1;
//	}
//	return 0;
//}

boolean getIPFromDomain(char* hostName, PWSTR ip) 
{
	//struct in_addr **addr_list;
	//struct hostent *he;
	//struct addrinfo hints, *result;
	ADDRINFOA hints, *result;
	void *ptr = nullptr;
	int errcode;

	memset(&hints, 0, sizeof(hints));

	//Caller will accept any protocol family supported by the os.
	hints.ai_family = PF_UNSPEC;

	//Provides sequenced, reliable, two - way, connection -
	//based byte streams.An out - of - band data transmission
	//mechanism may be supported.
	hints.ai_socktype = SOCK_STREAM;

	//If hints.ai_flags includes the AI_CANONNAME flag, then the ai_canon‐
	//name field of the first of the addrinfo structures in the returned
	//list is set to point to the official name of the host.
	hints.ai_flags |= AI_CANONNAME;

	errcode = getaddrinfo(hostName, NULL, &hints, &result);
	if (errcode != 0) 
	{
		printf("\ngethostbyname failed!", WSAGetLastError());
		return 1;
	}
	
	printf("\nHost: %s", hostName);

	while (result)
	{
		//Converts an IPv4 or IPv6 network address into a string in
		//internet standard format.
		InetNtopW(result->ai_family, result->ai_addr->sa_data, ip, 100);

		switch (result->ai_family)
		{
			case AF_INET:
				ptr = &((struct sockaddr_in *) result->ai_addr)->sin_addr;
				break;
			case AF_INET6:
				ptr = &((struct sockaddr_in6 *) result->ai_addr)->sin6_addr;
				break;
			default:
				printf("Invalid ai_family.");
				return 1;
		}
		InetNtopW(result->ai_family, ptr, ip, 100);
		printf("\nIPv%d address: %ls (%s)\n", result->ai_family == PF_INET6 ? 6 : 4,
			ip, result->ai_canonname);
		result = result->ai_next;
	}

	return 0;
}

void getIPfromSocket(int *family,struct sockaddr_in *sockAddr, char *ip)
{
	inet_ntop(*family, &(sockAddr->sin_addr), ip, INET_ADDRSTRLEN);
	printf("\nIP: %s", ip);
}

void getPortFromSocket(int *port, struct sockaddr_in *sockAddr)
{
	*port = ntohs(sockAddr->sin_port);
	printf("\nPort: %d", *port);
}

boolean getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr, int family)
{
	puts("\nInfo:");
	getIPfromSocket(&family, sockAddr, ip);
	getPortFromSocket(port, sockAddr);
	return 0;
}




