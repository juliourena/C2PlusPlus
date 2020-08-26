#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndpoint.h"

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
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	private:
		PResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}