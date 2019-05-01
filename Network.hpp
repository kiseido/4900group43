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
boolean connectToServer(SOCKET *s, struct sockaddr_in *server);
boolean sendData(SOCKET *s, char* message);
boolean receiveReply(SOCKET *s, char* server_reply);
boolean closeSocket(SOCKET *s);
boolean getIPFromDomain(char* hostName, PWSTR ip);