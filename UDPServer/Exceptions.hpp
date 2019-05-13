#pragma once

#include "Util.hpp"

class WSAException : public std::exception
{
private:
	std::string message;
public:
	WSAException(std::string message):message(message) {}
	const char * what() const throw() {
		const char * error = message.c_str();
		return error;
	}
};

class SocketException : public std::exception 
{
private:
	std::string message;
public:
	SocketException(std::string message) :message(message) {}
	const char * what() const throw() {
		const char * error = message.c_str();
		return error;
	}
};

class TCPException : public std::exception
{
private:
	std::string message;
public:
	TCPException(std::string message) :message(message) {}
	const char * what() const throw()
	{
		const char * error = message.c_str();
		return error;
	}
};

class UDPException : public std::exception 
{
private:
	std::string message;
public:
	UDPException(std::string message): message(message){}
	const char * what() const throw()
	{
		const char * error = message.c_str();
		return error;
	}
};
