// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


#include "Util.hpp"
#include "WSASession.hpp"
#include "UDPSocket.hpp"
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
		uSock.bindSock(&server);
		
		SOCKET s = uSock.getSock();
		//puts("Press Enter on client connection.");
		//getchar();

		puts("\nWaiting for data");
		while (true)
		{
			char buff[100];
			int buffLen = sizeof(buff);
			
			uSock.receiveFrom(&s, buff, buffLen, &sockAddr);

			printf("Received packet from %d\n",
				ntohs(sockAddr.sin_port));
			printf("Data: %s", buff);

			puts("\nSending Reply");

			buffLen = sizeof(buff);
			uSock.sendTo(&s, buff, buffLen, &sockAddr);
		}
		uSock.~UDPSocket();
	}
	catch (UDPException e) { puts(e.what()); }

}





