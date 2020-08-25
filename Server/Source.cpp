// Server code 
#include <C2PlusPlus/IncludeMe.h>
#include <iostream>

using namespace C2PlusPlus;

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
	}
	Network::Shutdown();
	system("pause");
	return 0;
}