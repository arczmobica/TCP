#include "stdafx.h"
#include <WinSock2.h>

#include "TCP_Client.hpp"

using namespace std;

template<int value>
struct Version
{
	static const WORD value{ MAKEWORD(value,value) };
};

TCP_Client::TCP_Client()
{
	//1. Do init here, don't depend on user that he will do it
	
	

	printf("\nInitialising Winsock...");
	//
	//Version<2>::value
	if (WSAStartup(MAKEWORD(2, 2), &wsa_) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		throw runtime_error("Cannot initialize Winsock");
	}

	printf("Winsock Initialised.");


}


int TCP_Client::send_msg(SOCKET s, const std::string& msg)
{
	return send(s, msg.c_str(), msg.length(), 0);
}

TCP_Client::~TCP_Client()
{
	//close sockets?
}

SOCKET TCP_Client::create_socket(int address_family, int socket_type, int protocol)
{
	return socket(address_family, socket_type, protocol);
}

int TCP_Client::close_socket(SOCKET s)
{
	return closesocket(s);
}