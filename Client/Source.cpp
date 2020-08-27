// Client code 
#include <C2PlusPlus\IncludeMe.h>
#include <iostream>
#include <Client\Metadata.h>

using namespace C2PlusPlus;

int main()
{
	/*Client::Metadata metadata;
	std::string username = metadata.GetCurrentUserName();
	std::cout << "Username: " << username << std::endl;*/

	Client::Metadata metadata;
	std::cout << "Username: " << metadata.username << std::endl; 
	std::cout << "Proccess ID: " << metadata.processId << std::endl;

	/*if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		Socket socket;

		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 8888)) == PResult::P_Success)
			{
				std::cout << "Successfully connected to server!" << std::endl;

				Module module;

				std::string buffer = module.Cmd("whoami");

				while (true)
				{
					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					int result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != PResult::P_Success)
						break;

					result = socket.SendAll(buffer.data(), buffer.size());
					if (result != PResult::P_Success)
						break;

					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
			}
			else
			{
				std::cerr << "Failed to connect to server." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;
		}
	}*/
	Network::Shutdown();
	system("pause");
	return 0;
}