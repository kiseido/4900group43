#pragma once

#include "Util.hpp";
#include "Socket.hpp"

class UDPSocket : public Socket
{
private:
	//void create();
public:
	/*Constructor creates a UDP socket that defaults to IPv4
	address type.*/
	UDPSocket();

	/*Constructor that creates a UDP socket and allows you to set
	the address type
	@param addrType the address type you desire(IPv4 or IPv6).*/
	UDPSocket(int addrType);

	//Destructor destroys UDPSocket
	~UDPSocket();

	/*Sends a packet to a specified socket.
	@param s descriptor identifying a socket to send to.
	@param sendBuff pointer to buffer containing data to be transmitted
	@param buffLen length in bytes of the data pointed to by sendBuff
	@param recvAddr pointer to sockaddr struct containing addrInfo of
	target socket. 
	@throws UDPException*/
	void sendTo(SOCKET *s, const char* sendBuff, int buffLen,
		struct sockaddr_in *recvAddr);

	/*Receives packet from specified socket
	@param s descriptor identifying a socket to receive from
	@param recvBuff pointer to buffer to store received packet data
	@param buffLen length of buffer pointed to by recvBuff
	@param srcAddr pointer to sockaddr struct containing addrInfo of
	target socket.
	@return 0 if connection closed, SOCKET_ERROR if error, else number
	of bytes received.
	@throws UDPException*/
	int receiveFrom(SOCKET *s, char * recvBuff, int buffLen,
		struct sockaddr_in *srcAddr);

	SOCKET getSock()
	{
		return sock;
	}

};