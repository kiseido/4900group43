/*
	Initialize Winsock
*/

#include "Network.hpp"

#pragma comment(lib, "ws2_32.lib")//Winsock library


//Initialize Winsock
boolean initWinsockLibrary(WSADATA *wsa) 
{
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), wsa))
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("\nInitialized.");

	return 0;
}

//Create a socket
boolean createSocket(SOCKET *s) 
{
	//Address Family : AF_INET(this is IP version 4)
	//Type : SOCK_STREAM(this means connection oriented TCP protocol)
	//Protocol : 0[or IPPROTO_TCP, IPPROTO_UDP]
	if ((*s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		return 1;
	}

	printf("\nSocket created.");
	return 0;
}

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

boolean sendData(SOCKET *s, char* message)
{
	if (send(*s, message, strlen(message), 0) < 0)
	{
		puts("\nSend Failed");
		return 1;
	}
	puts("Data Sent");
}

boolean receiveReply(SOCKET *s, char* server_reply)
{
	int recv_size;

	if ((recv_size = recv(*s, server_reply, 2000, 0)) == SOCKET_ERROR)
	{
		puts("Receive Failed");
		return 1;
	}

	puts("Reply Received");
	
	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';

	return 0;
}

boolean closeSocket(SOCKET *s) {
	closesocket(*s);
	WSACleanup();

	return 0;
}

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
		}
		InetNtopW(result->ai_family, ptr, ip, 100);
		printf("\nIPv%d address: %ls (%s)\n", result->ai_family == PF_INET6 ? 6 : 4,
			ip, result->ai_canonname);
		result = result->ai_next;
	}

	return 0;

	////Cast the h_addr_list to in_addr, since h_addr_list also 
	////has the ip address in long format only
	//addr_list = (struct in_addr **) he->h_addr_list;

	//for (int i = 0; addr_list[i] != NULL; i++) 
	//{
	//	//Return the first one;
	//	strcpy_s(ip, sizeof(char) * 100, inet_ntoa(*addr_list[i]));
	//}

	//printf("%s resolved to : %s\n", hostName, ip);
	//return 0;

}