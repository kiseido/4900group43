#include <stdio.h>
#include <stdlib.h>
#include <Ws2tcpip.h>

#define IPv4 AF_INET
#define IPv6 AF_INET6
#define LOCAL_HOST "127.0.0.1"
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
#define AUTO 0