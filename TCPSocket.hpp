#pragma once
#include "Util.hpp"
#include "Socket.hpp"


class TCPSocket : public Socket
{
private:

public:

	/*Constructor creates a TCP Socket that defaults to IPv4 
	address type.*/
	TCPSocket();

	/*Constructor creates a TCP Socket and allows you to set 
	the address type.
	@param addrType the addressType you desire(IPv4 or IPv6).*/
	TCPSocket(int addrType);
	
	/*Destructor closes the socket. */
	~TCPSocket();

	/*	Sends message to specified socket
	@param message message to be sent.
	@param clientSock the socket descriptor for the socket
	you want to send to.
	@throws TCPException*/
	void sendTo(const char * message, SOCKET *clientSock);

	/* Listens for incoming connections on current bound
	socket
	@param maxConQueue specifies the maximum connections
	@throws TCPException if fails*/
	void listenForConnections(int maxConQueue);

	/* Accepts an incoming connection from a client & saves the socket information
	in client
	@param client sockaddr_in structure to contain client info like port & ip address
	@return new Socket object pointer representing the client socket.
	@throws TCPException or UDPException if fails*/
	SOCKET acceptConnection(struct sockaddr_in *client);

	/*  Receives a message from specified socket
	stores it in the receivedMessages queue if there is 
	a message.
	@param buffSize the max buffer size in bytes for the 
	received message
	@return 0 if connection closed, SOCKET_ERROR if error, 
	or number of bytes received.*/
	int receiveFrom(SOCKET *otherSocket, const int &buffSize);


	void connectToServer(struct sockaddr_in *server);

	SOCKET* getSock()
	{
		return &sock;
	}
};

