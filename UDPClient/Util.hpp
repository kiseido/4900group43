#include <stdio.h>
#include <stdlib.h>
#include <Ws2tcpip.h>
#include <vector>
#include <thread>
#include <mutex>
#include "Exceptions.hpp"
#include <queue>
#include <iostream>
#include <string>


#define IPv4 AF_INET
#define IPv6 AF_INET6
#define LOCAL_HOST "127.0.0.1"
#define TCP IPPROTO_TCP
#define UDP IPPROTO_UDP
#define AUTO 0
#define MAX_BACKLOG SOMAXCONN