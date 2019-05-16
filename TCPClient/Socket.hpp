#pragma once
#include "Util.hpp"

class Socket
{
private:

protected:
	int addrType, sockType, protocol;
	sockaddr_in sockAddr;
	char ip[40];
	int port;
	SOCKET sock;
	std::queue<char*> receivedMessages;
	std::string error = "";

	/* Creates a socket using class members addrType, sockType
	& protocol and saves socket descriptor in class member sock
	@throws TCPException or UDPException if fails*/
	void create();

public:
	std::vector<SOCKET> clients;
	/* Initializes sockaddr_in structure sockAddr using 
	the ip address & port number 
	@param sockAddr the structure you want to fill
	@param addr the ip address
	@param port the port number
	@throws SocketException if fails*/
	void setupSockAddr(struct sockaddr_in *sockAddr, const char* addr, int port);
	
	/* Binds socket to port and address associated with 
	the sockaddr_in structure
	@param sockAddr the structure containing ip address &
	port information
	@throws TCPException or UDPException if fails*/
	void bindSock(struct sockaddr_in *sockAddr);

	/* Extracts the IP address as a char * from sockAddr & stores it in ip
	@param sockAddr structure containing socket information
	@param ip char * that is meant to contain the extracted IP*/
	void getIPfromSockAddr(struct sockaddr_in *sockAddr, char *ip);

	/* Extracts the Port number as an int from sockAddr & stores it in port
	@param sockAddr structure containing socket information
	@param port int that is meant to contain the extracted port number*/
	void getPortFromSockAddr(struct sockaddr_in *sockAddr, int *port);
	void getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr);
	
	/*Closes the socket specified
	@param s socket descriptor*/
	void closeSocket(SOCKET *s);

	/*Closes socket associated with this object*/
	void closeSocket();

	void getIPFromDomain(char* hostName, char* fetchedIP);

	//virtual void sendTo(SOCKET clientSock, const char * message) = 0;

};