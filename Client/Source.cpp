// Client code 
#include <C2PlusPlus\IncludeMe.h>
#include <iostream>

using namespace C2PlusPlus;

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		Socket socket;

		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	return 0;
}