#include <stdio.h>
#include "WSASession.hpp"
#include "Exceptions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "Util.hpp"
#include <sstream>

void processSend(TCPSocket *tSock);
void checkHeader(TCPSocket * tSock, std::string message);
void holePunch(TCPSocket *tSock, const char * addr, int port);
std::vector<std::string> parseString(std::string *message);
void processReply(SOCKET s, TCPSocket *tSock);

int main()
{
	puts("TCP Client Test! XD");
	WSASession wsa;
	//try {
	//	wsa = WSASession();
	//}
	//catch (WSAException e) { puts(e.what()); }

	TCPSocket tSock;
	sockaddr_in serverAddr;
	
	//CHANGE THESE TO WHAT YOU WANT
	//const char * addr = "142.232.142.251";
	//const char * addr = "198.105.215.35";
	const char * addr = LOCAL_HOST;
	int port = 8080;

	try {
		char domain[] = "node.digitalprojects.info";
		char fetchedIP[100];
		tSock.getIPFromDomain(domain, fetchedIP);
		
		tSock.setupSockAddr(&serverAddr, fetchedIP, port);

		tSock.connectToServer(&serverAddr);

		std::thread thrSend(processSend, &tSock);
		thrSend.detach();

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
			std::cout << "Server has disconnected.";
			tSock->closeSocket(&s);
			break;
		}
		std::thread tReply(checkHeader, tSock, receiveMessage);
		tReply.detach();
		std::cout << "Reply: " << receiveMessage << '\n';
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
		std::cout << "Client Port: " << clientPort;
	}
}

void checkHeader(TCPSocket * tSock, std::string message)
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
	//Game Client Code
	try 
	{
		const char * internalAddr = "192.168.43.103";
		TCPSocket cSock(IPv4);
		sockaddr_in sockAddrConnect;
		cSock.setupSockAddr(&sockAddrConnect, addr, port);
		sockaddr_in sockAddrBind;
		cSock.setupSockAddr(&sockAddrBind, internalAddr, 8080);
		while (true) {
			try {
				cSock.connectToServer(&sockAddrConnect);
			}
			catch (TCPException e) { puts(e.what()); };
		}






;


	}
	catch (TCPException e) { 
		puts(e.what());
		exit(1);
	}

}

void hostServer(Socket *tSock)
{

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

