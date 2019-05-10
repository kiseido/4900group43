#include "Socket.hpp"

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
	printf("\nPort: %d", *port);
}

void Socket::getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr)
{
	puts("\nInfo:");
	getIPfromSockAddr(sockAddr, ip);
	getPortFromSockAddr(sockAddr, port);
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
