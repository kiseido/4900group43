#include <stdio.h>
#include "WSASession.hpp"
#include "Exceptions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "Util.hpp"
#include <sstream>

void processSend(TCPSocket *tSock);
void checkHeader(TCPSocket * tSock, std::string message, std::thread::id receiveThread);
void holePunch(TCPSocket *tSock, const char * addr, int port);
std::vector<std::string> parseString(std::string *message);
void processReply(SOCKET s, TCPSocket *tSock);
void servePunch(TCPSocket *tSock, const char * addr);
void conPunch(TCPSocket *tSock, const char *addr, int port);

int main()
{
	puts("TCP Game Server Test! XD");

	WSASession wsa;
	TCPSocket tSock;
	sockaddr_in serverAddr, localAddr;

	//CHANGE THESE TO WHAT YOU WANT
	//const char * addr = "142.232.142.251";
	//const char * addr = "198.105.215.35";
	//const char * addr = LOCAL_HOST;
	int port = 8080;

	try {
		char domain[] = "node.digitalprojects.info";
		char fetchedIP[100];
		tSock.getIPFromDomain(domain, fetchedIP);
		tSock.setupSockAddr(&serverAddr, fetchedIP, port);

		tSock.connectToServer(&serverAddr);

		int optVal = 1;
		sockaddr_in localAddr;
		char ip[100];
		tSock.setSockOptions(SO_REUSEADDR, (char *)&optVal, sizeof(int));
		tSock.getSockName(&localAddr);
		tSock.getPortFromSockAddr(&localAddr, &tSock.internalPort);

		char key[] = GAME_CONNECTION;
		tSock.sendTo(key);

		char message[6];
		//_itoa_s(tSock.internalPort, message, 10);
		//tSock.sendTo(message);

		//std::thread thrSend(processSend, &tSock);
		//thrSend.detach();

		processReply(*tSock.getSock(), &tSock);
	}
	catch (TCPException e) { puts(e.what()); }

	getchar();
}

void processSend(TCPSocket *tSock)
{
	std::string message;
	while (true)
	{
		getline(std::cin, message);
		const char * cMessage = message.c_str();
		tSock->sendTo(cMessage);
	}
}

void processReply(SOCKET s, TCPSocket *tSock)
{
	char receiveMessage[100];
	int result;
	while (true)
	{
		if (tSock->receiveFrom(&s, 100, receiveMessage) == 0)
		{
			std::cout << "User " << s << " has Disconnected.";
			tSock->closeSocket(&s);
			break;
		}
		std::thread tReply(checkHeader, tSock, receiveMessage, std::this_thread::get_id());
		tReply.detach();
		std::cout << "\nReply: " << receiveMessage << '\n';
	}
}

void processAccept(TCPSocket *sock)
{
	sockaddr_in clientAddr;
	SOCKET newClient;
	for (int index = 0; (newClient = sock->acceptConnection(&clientAddr)) != INVALID_SOCKET; index++)
	{
		sock->clients.push_back(newClient);
		//std::thread conThread(*processClient, newClient, &tSock, index);
		//conThread.detach();
		int clientPort;
		sock->getPortFromSockAddr(&clientAddr, &clientPort);
		std::cout << "\nClient Port: " << clientPort;
	}
}

void checkHeader(TCPSocket * tSock, std::string message, std::thread::id receiveThread)
{
	std::vector<std::string> parStrings = parseString(&message);
	std::string str = parStrings.at(0);
	if (!str.compare(HOLE_PUNCH))
	{
		const char * addr = parStrings.at(2).c_str();
		int port = std::stoi(parStrings.at(1));
		holePunch(tSock, addr, port);
	}
	else if (!str.compare(HOST_SERVER))
	{

	}
}

void holePunch(TCPSocket *tSock, const char * addr, int port)
{
	std::thread tServePunch(servePunch, tSock, addr);
	tServePunch.detach();

	conPunch(tSock, addr, port);
}

void conPunch(TCPSocket * tSock, const char * addr, int port)
{
	try
	{
		TCPSocket cSock(IPv4);
		int optVal = 1;
		cSock.setSockOptions(SO_REUSEADDR, (char *)&optVal, sizeof(int));
		sockaddr_in sockAddrConnect;
		cSock.setupSockAddr(&sockAddrConnect, addr, port);
		

		sockaddr_in privateAddr;
		tSock->getSockName(&privateAddr);
		int port;
		tSock->getPortFromSockAddr(&privateAddr, &port);
		char internalAddr[100];
		tSock->getIPfromSockAddr(&privateAddr, internalAddr);

		sockaddr_in sockAddrBind;
		cSock.setupSockAddr(&sockAddrBind, internalAddr, tSock->internalPort);
		try
		{
			cSock.bindSock(&sockAddrBind);
		}
		catch (TCPException e) { 
			puts("ConPunch BindSock Failed;");
			puts(e.what());
		}

		while (true)
		{
			try
			{
				cSock.connectToServer(&sockAddrConnect);
			}
			catch (TCPException e) { puts(e.what()); }
		}
	}
	catch (TCPException e) {
		puts(e.what());
		getchar();
		exit(1);
	}
}

void servePunch(TCPSocket *tSock, const char * addr)
{
	try
	{
		sockaddr_in privateAddr;
		tSock->getSockName(&privateAddr);
		int port;
		tSock->getPortFromSockAddr(&privateAddr, &port);
		char internalAddr[100];
		tSock->getIPfromSockAddr(&privateAddr, internalAddr);
		TCPSocket cSock(IPv4);
		bool optVal= true;
		cSock.setSockOptions(SO_REUSEADDR, (char *)&optVal, sizeof(int));
		//sockaddr_in sockAddrConnect;
		//cSock.setupSockAddr(&sockAddrConnect, addr, port);
		sockaddr_in sockAddrBind;

		cSock.setupSockAddr(&sockAddrBind, internalAddr, tSock->internalPort);
		try
		{
			cSock.bindSock(&sockAddrBind);
		}
		catch (TCPException e) {
			puts("ServePunch BindSock Failed;");
			puts(e.what());
		}

		cSock.listenForConnections(1);

		processAccept(&cSock);

		//std::thread tAccept(processAccept, &cSock);
		//tAccept.detach();
		//getchar();
	}
	catch (TCPException e) {
		puts(e.what());
		getchar();
		exit(1);
	}
}

std::vector<std::string> parseString(std::string *message)
{
	std::string parsed;
	std::vector<std::string> values;
	std::stringstream ss(*message);
	while (getline(ss, parsed, ' '))
	{
		values.push_back(parsed);
	}
	values.at(0);
	return values;
}

