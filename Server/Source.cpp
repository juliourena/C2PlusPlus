// Server code 
#include <C2PlusPlus/IncludeMe.h>
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
			if (socket.Listen(IPEndpoint("0.0.0.0", 8888)) == PResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 8888." << std::endl;
				Socket newConnection;
				if (socket.Accept(newConnection) == PResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;

					std::string buffer = "";
					while (true)
					{
						uint32_t bufferSize = 0;
						int result = newConnection.RecvAll(&bufferSize, sizeof(uint32_t));
						if (result != PResult::P_Success)
							break;

						bufferSize = ntohl(bufferSize);

						if (bufferSize > g_MaxPacketSize)
							break;

						buffer.resize(bufferSize);
						result = newConnection.RecvAll(&buffer[0], bufferSize);
						if (result != PResult::P_Success)
							break;

						std::cout << "[" << bufferSize << "]" << buffer << std::endl;
					}
					newConnection.Close();
				}
				else
				{
					std::cerr << "Failed to accept new connection." << std::endl;
				}
			}
			else
			{
				std::cerr << "Failed to Listen on port 8888." << std::endl;
			}

			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}