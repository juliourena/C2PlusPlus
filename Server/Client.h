#pragma once
#include <string>

struct Client
{
	std::string username;
	std::string processName;
	int processId;
	int is64;
};