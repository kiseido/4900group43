#include "Socket.hpp"
#include <comdef.h>

void Socket::setupSockAddr(struct sockaddr_in *sockAddr, const char* addr, int port)
{
	int result = inet_pton(addrType, addr, &sockAddr->sin_addr.s_addr);
	if (result == 0)
	{
		error = "\nSetup SockAddr Failed. Invalid IPv4 or IPv6 string.";
		throw(SocketException(error));
	}
	else if (result == -1)
	{
		error = "\nSetup SockAddr Failed. Error code: " + 
			std::to_string(WSAGetLastError());
		throw(SocketException(error));
	}
	sockAddr->sin_family = addrType;
	sockAddr->sin_port = htons(port);

}

void Socket::bindSock(struct sockaddr_in *sockAddr) 
{
	if (bind(sock, (struct sockaddr *)sockAddr, sizeof(*sockAddr)) == SOCKET_ERROR)
	{
		error = "\nBind failed with error code : " +
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
	}
	puts("\nBind done!");
}

void Socket::create()
{
	if ((sock = socket(addrType, sockType, protocol)) == INVALID_SOCKET)
	{
		error = "Could not create socket : " + 
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
	}
	printf("\nSocket created.");
}

void Socket::getIPfromSockAddr(struct sockaddr_in *sockAddr, char *ip)
{
	inet_ntop(addrType, &(sockAddr->sin_addr), ip, INET_ADDRSTRLEN);
	printf("\nIP: %s", ip);
}
void Socket::getPortFromSockAddr(struct sockaddr_in *sockAddr, int *port)
{
	*port = ntohs(sockAddr->sin_port);
	printf("\nMy Local Port: %d", *port);
}

void Socket::getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr)
{
	puts("\nInfo:");
	getIPfromSockAddr(sockAddr, ip);
	getPortFromSockAddr(sockAddr, port);
}

void Socket::closeSocket()
{
	if (closesocket(sock) == SOCKET_ERROR)
	{
		error = "Close Socket Failed. Error code : " +
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
	}
}

void Socket::closeSocket(SOCKET *s) {
	if (closesocket(*s) == SOCKET_ERROR)
	{
		error = "Close Socket Failed. Error code : " +
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
	}
}

void Socket::getIPFromDomain(char* hostName, char * fetchedIP)
{
	WCHAR ip[100];
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

	if ((errcode = getaddrinfo(hostName, NULL, &hints, &result)) != 0)
	{
		error = "getaddrinfo Failed. Error code : " +
			std::to_string(WSAGetLastError());
		if (protocol == TCP)
		{
			throw TCPException(error);
		}
		else if (protocol == UDP)
		{
			throw UDPException(error);
		}
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
			error = "Invalid ai_family!";
			if (protocol == TCP)
			{
				throw TCPException(error);
			}
			else if (protocol == UDP)
			{
				throw UDPException(error);
			}
		}
		InetNtopW(result->ai_family, ptr, ip, 100);		
		_bstr_t b(ip);
		char * temp = b;
		for (int i = 0; i < 100; i++)
		{
			fetchedIP[i] = temp[i];
		}
		printf("\nIPv%d address: %s (%s)\n", result->ai_family == PF_INET6 ? 6 : 4,
			fetchedIP, result->ai_canonname);
		result = result->ai_next;
	}
}

void Socket::setSockOptions(int optName, const char * optVal, int optLen)
{

	if (setsockopt(sock, SOL_SOCKET, optName, optVal, sizeof(&optVal)) == SOCKET_ERROR)
	{
		std::string error = "Set Sock Options. Error code: " +
			std::to_string(WSAGetLastError());
		throw(SocketException(error));
	}
	puts("Socket option set.");
}

void Socket::getSockName(sockaddr_in *name)
{
	puts("\nGetting Sock Name...");
	int len = sizeof(*name);
	if (getsockname(sock, (struct sockaddr*)name, &len) == SOCKET_ERROR)
	{
		std::string error = "Get Sock Name failed. Error code: " +
			std::to_string(WSAGetLastError());
		throw(SocketException(error));
	}
	puts("\nRetrieved Sock name successfully.");
}