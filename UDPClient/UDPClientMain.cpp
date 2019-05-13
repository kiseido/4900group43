// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


#include "Util.hpp"
#include "WSASession.hpp"
#include "UDPSocket.hpp"
#include <regex>
//#include <GL/glew.h>

int main()
{
	//UDP Test
	WSASession wsa;
	struct sockaddr_in server, sockAddr;

	try {
		wsa = WSASession();
	}
	catch (WSAException e) { puts(e.what()); }
	
	try {
		UDPSocket uSock(IPv4);
		uSock.setupSockAddr(&server, LOCAL_HOST, 8888);
		//uSock.bindSock(&server);
		
		SOCKET s = uSock.getSock();
		
		//puts("Press Enter on client connection.");
		//getchar();

		//puts("\nWaiting for data");
		
		std::string message;
		char buff[512];
		while (true)
		{
			std::cout << "\nEnter Message: ";
			getline(std::cin, message);			
			uSock.sendTo(&s, message.c_str(), message.length(), &server);
			if (uSock.receiveFrom(&s, buff, 512, &server) == 0)
			{
				std::cout << "Server Disconnected";
				uSock.closeSocket();
				break;
			}
			std::string response(buff);
			response = std::regex_replace(response, std::regex(" +$"), "");
			std::cout << response << '\n';

		}
		uSock.~UDPSocket();
	}
	catch (UDPException e) { puts(e.what()); }

}





