// TCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "C_Socket_API.hpp"
#include "TCP_Client.hpp"

vector<string> parse_args(const int argc,const char*const* args_)
{
	using vec_of_string = vector<string>;
	vec_of_string res;
	for (int i{ 1 }; i < argc;++i)
	{/*first argc is name of a program, so skip it, i.e. init with 1*/
		auto v = *(args_ + i) ;
		res.push_back( v );
	}
	return res;
}

//int main(int argc, char** argv)
//{
//	try
//	{
//		TCP_Client client;
//		//Address_Family<AF_INET6>(), Socket_Type<SOCK_STREAM>(), Protocol::None
//		SOCKET aSocket;
//		if ((aSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
//		{
//			printf("Could not create socket : %d", WSAGetLastError());
//		}
//		aSocket = { client.create_socket(Address_Family<AF_INET6>(), Socket_Type<SOCK_STREAM>(), Protocol::None) };
//		if (aSocket == INVALID_SOCKET)
//		{
//			puts("Invalid Socket");
//		}
//
//		
//
//		sockaddr_in server;
//		//inet_addr("74.125.235.20")
//		//server.sin_addr.s_addr = inet_addr("74.125.235.20");
//		//server.sin_family = AF_INET6;
//		//server.sin_port = htons(80);
//		//server.sin_addr.S_un.S_addr = inet_pton(Address_Family<AF_INET6>(), "74.125.235.20", 0);// inet_pton(Address_Family<AF_INET6>(),"74.125.235.20",0);//inet_addr has been deprecated
//		server.sin_addr.s_addr = inet_addr("74.125.235.20");
//		server.sin_family = AF_INET;
//		server.sin_port = htons(80);
//		if (connect(aSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
//		{
//			puts("connect error");
//			return 1;
//		}
//		if (connect(aSocket, (sockaddr*)&server, sizeof(server)) < 0)
//		{
//			puts("Cannot connect");
//		}
//		else
//		{
//			puts("Connected");
//		}
//	}
//	catch (const runtime_error& runtime_err)
//	{
//		printf(runtime_err.what());
//
//	}
//
//	
//}

int main(int argc, char *argv[])
{

	SOCKET s;
	sockaddr_in server;
	TCP_Client client;
	/*printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");*/

	//Create a socket
	s = { client.create_socket(Address_Family<AF_INET>(), Socket_Type<SOCK_STREAM>(), Protocol::None) };
	
	

	//74.125.235.20
	//
	//GET / HTTP/1.1\r\n\r\n
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	puts("Connected");

	if (client.send_msg(s,"GET / HTTP/1.1\r\n\r\n") < 0)
	{
		puts("Cannot send");
	}
	puts("Message sent");

	//Receive a reply from the server
	int recv_size{0};
	char server_reply[2000];
	if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);
	client.close_socket(s);
	return 0;
}