#include "UDPSocket.hpp"

UDPSocket::UDPSocket() 
{
	addrType = IPv4;
}

UDPSocket::UDPSocket(int addrType) {
	this->addrType = addrType;
}

UDPSocket::~UDPSocket() {
	closesocket(*sock);
}

void UDPSocket::create()
{
	if ((*sock = socket(addrType, SOCK_DGRAM, UDP)) == INVALID_SOCKET)
	{
		const char * message = "Could not create socket : " +
			WSAGetLastError();
		throw TCPException(message);
		puts(message);
	}
	printf("\nSocket created.");
}
//void sendTo(SOCKET *clientSock, const char* sendBuff)
//{
//	if(sendto(*clientSock, sendBuff, BufLen, 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr)) == SOCKET_ERROR);
//	if (iResult == SOCKET_ERROR) {
//		wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
//		closesocket(SendSocket);
//		WSACleanup();
//		return 1;
//}

