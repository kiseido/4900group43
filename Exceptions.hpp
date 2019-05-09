#pragma once

#include "Util.hpp"

class WSAException : public std::exception
{
private:
	const char * message;
public:
	WSAException(const char * message):message(message) {}
	const char * what() const throw() {
		return message;
	}
};

class TCPException : public std::exception
{
private:
	const char * message;
public:
	TCPException(const char * message):message(message){}
	const char * what() const throw()
	{
		return message;
	}
};

class UDPException : public std::exception 
{
private:
	const char * message;
public:
	UDPException(const char * message): message(message){}
	const char * what() const throw()
	{
		return message;
	}
};
