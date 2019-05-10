#include "UDPSocket.hpp"

UDPSocket::UDPSocket() 
{
	addrType = IPv4;
	protocol = UDP;
	sockType = SOCK_DGRAM;
	create();
}

UDPSocket::UDPSocket(int addrType) {
	this->addrType = addrType;
	protocol = UDP;
	sockType = SOCK_DGRAM;
	create();
}

UDPSocket::~UDPSocket() {
	closesocket(sock);
}

void UDPSocket::sendTo(SOCKET *s, const char* sendBuff, int buffLen, 
	struct sockaddr_in *recvAddr)
{
	if (sendto(*s, sendBuff, buffLen, 0,
		(struct sockaddr *)recvAddr, sizeof(*recvAddr)) == SOCKET_ERROR)
	{
		std::string error = "\nSend Failed. Error code : " +
			std::to_string(WSAGetLastError());
		throw UDPException(error);
	}
}

int UDPSocket::receiveFrom(SOCKET *s, char * recvBuff, int buffLen,
	struct sockaddr_in *srcAddr)
{
	memset(recvBuff, '\0', buffLen);
	int addrLen = sizeof(*srcAddr);
	int recvLen;
	if ((recvLen = recvfrom(*s, recvBuff, buffLen, 0, (struct sockaddr *)srcAddr, &addrLen)) == SOCKET_ERROR)
	{
		std::string error = "\nReceive Failed. Error code : " +
			std::to_string(WSAGetLastError());
		throw UDPException(error);
	}
	return recvLen;
}




