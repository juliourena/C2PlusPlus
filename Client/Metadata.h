#pragma once
#include <string>

namespace Client
{
	class Metadata
	{
	public:
		Metadata();
		void GetCurrentUserName();
		void GetCurrentProccessInfo();
		std::string username = "";
		int processId = 0;
		std::string processName = "";
		int is64 = 0;
	private:
		std::string hostname = "";
	};
}