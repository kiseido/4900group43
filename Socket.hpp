#pragma once
#include "Util.hpp"

class Socket
{
private:

protected:
	void create();

	int addrType, sockType, protocol;
	
	SOCKET sock;
	std::queue<char*> receivedMessages;
	std::string error = "";
public:

	/* Initializes sockaddr_in structure sockAddr using 
	the ip address & port number 
	@param sockAddr the structure you want to fill
	@param addr the ip address
	@param port the port number*/
	void setupSockAddr(struct sockaddr_in *sockAddr, const char* addr, int port);
	
	/* Listens for incoming connections on current bound
	ip address & port
	@param maxConQueue specifies the maximum connections*/
	void listenforConnections(int maxConQueue);
	
	/* Binds socket to port and address associated with 
	the sockaddr_in structure
	@param sockAddr the structure containing ip address &
	port information*/
	void bindSock(struct sockaddr_in *sockAddr);

	//virtual void sendTo(SOCKET clientSock, const char * message) = 0;

	void getIPfromSocket(struct sockaddr_in *sockAddr, char *ip);
	void getPortFromSocket(struct sockaddr_in *sockAddr, int *port);
	void getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr, int family);
	
	SOCKET acceptConnection(struct sockaddr_in *sockAddr);

};