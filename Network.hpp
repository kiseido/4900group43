#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <sys/types.h>

#include <ws2ipdef.h>
#include <ws2tcpip.h>

#include <string>

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

//#include <netdb.h>

//#include <sys/socket.h>
//#include <arpa/inet.h>

boolean initWinsockLibrary(WSADATA *wsa);
boolean createSocket(SOCKET *s);
boolean setupServer(struct sockaddr_in *server, const char* addr, int family, int port);
boolean connectToServer(SOCKET *s, struct sockaddr_in *server);
boolean sendData(SOCKET *s, char* message);
boolean receiveReply(SOCKET *s, char* server_reply);
boolean closeSocket(SOCKET *s);
boolean getIPFromDomain(char* hostName, PWSTR ip);
boolean bindSocket(struct sockaddr_in *server, SOCKET *s);
boolean listenforConnections(SOCKET *s, int maxConQueue);
boolean acceptConnection(SOCKET *s, SOCKET *newSocket, struct sockaddr_in *client);
boolean cleanupWSA();
boolean closeAndCleanup(SOCKET *s);