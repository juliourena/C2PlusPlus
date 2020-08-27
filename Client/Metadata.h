#pragma once
#include <string>

namespace Client
{
	class Metadata
	{
	public:
		Metadata();
		std::string GetCurrentUserName();
		void GetCurrentProccessInfo();
		std::string username = "";
		int processId = 0;
	private:
		std::string hostname = "";
	};
}