#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndpoint.h"
#include "Constants.h"

namespace C2PlusPlus
{
	class Socket
	{
	public:
		// Constructor
		Socket(	IPVersion ipversion = IPVersion::IPv4,
				SocketHandle handle = INVALID_SOCKET);
		PResult Create();
		PResult Close();
		PResult Bind(IPEndpoint endpoint);
		PResult Listen(IPEndpoint endpoint, int backlog = 5); // backlog how many connection we will received
		PResult Accept(Socket & outSocket);
		PResult Connect(IPEndpoint endpoint);
		PResult Send(const void * data, int numberOfBytes, int & bytesSent);
		PResult Recv(void * destination, int numberOfBytes, int & bytesReceived);
		PResult SendAll(const void * data, int numberOfBytes);
		PResult RecvAll(void * destination, int numberOfBytes);
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	private:
		PResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}