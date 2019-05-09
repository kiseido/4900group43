#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <sys/types.h>
#include "Util.hpp"
#include <ws2ipdef.h>
#include <ws2tcpip.h>

#include <string>

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

//#include <netdb.h>

//#include <sys/socket.h>
//#include <arpa/inet.h>

struct Connection
{
	struct sockaddr_in * addr_in;
	SOCKET * sock;
};




class Network
{
public:
	//WSASession
	//boolean initWinsockLibrary(WSADATA *wsa);
	//boolean cleanupWSA();

	//TCP Socket
	//boolean createSocket(SOCKET *s, int protocol);
	//boolean send(SOCKET *s, char* message);

	//UDP Socket

	//Other
	//boolean setupSockAddr(struct sockaddr_in *server, const char* addr, int family, int port);
	boolean connectToServer(SOCKET *s, struct sockaddr_in *server);

	//boolean receive(SOCKET *s, char* server_reply, int buffSize);
	boolean getIPFromDomain(char* hostName, PWSTR ip);
	//boolean bindSocket(struct sockaddr_in *server, SOCKET *s);
	//boolean listenforConnections(SOCKET *s, int maxConQueue);
	boolean acceptConnection(SOCKET *s, SOCKET *newSocket, struct sockaddr_in *client);
	//boolean acceptConnection(SOCKET *s, SOCKET *newSocket, struct sockaddr_in *client);
	boolean liveServer(SOCKET *s, std::vector<Connection> *connections, std::thread &tServerLoop);

	boolean closeSocket(SOCKET *s);

	//void getIPfromSocket(int *family, struct sockaddr_in *sockAddr, char *ip);
	//void getPortFromSocket(int *port, struct sockaddr_in *sockAddr);
	//boolean getSockAddrInfo(char *ip, int *port, struct sockaddr_in *sockAddr, int family);
	void serverLoop(SOCKET *s, std::vector<Connection> *connections);
	void receiveLoop(SOCKET *s, std::vector<char*> receivedMessages, int buffSize);
	boolean receiveMessages(SOCKET *s, std::vector<char*> &receivedMessages, std::thread &tReceiveLoop, int buffSize);
	//boolean closeAndCleanup(SOCKET *s);
	//boolean send(SOCKET *newSocket, char* message);
};

