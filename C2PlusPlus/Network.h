#pragma once
#define WIN32_LEAN_AND_MEAN 

#include <WinSock2.h>

namespace C2PlusPlus
{
	class Network
	{
	public:
		static bool Initialize();
		static void Shutdown();
	};
}