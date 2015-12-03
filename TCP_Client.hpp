#pragma once
#include <Ws2tcpip.h>
template<int value>
struct Address_Family
{
	static const int value_{value};
	operator int()
	{
		return value_;
	}
};


template<int value>
struct Socket_Type
{
	static const int value_{ value };
	operator int()
	{
		return value_;
	}
};

struct Address_Family_ : public Address_Family<2>
{
	operator int()
	{
		return value_;
	}
};

enum Protocol { None };

class TCP_Client
{
private:
	WSADATA wsa_={};//field used to start up winsock
public:
	TCP_Client();
	virtual ~TCP_Client();

	SOCKET create_socket(int address_family, int socket_type,int protocol);
	unsigned long send_msg(SOCKET s, const std::string& msg);
};

