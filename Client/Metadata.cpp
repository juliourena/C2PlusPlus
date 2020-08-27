#include "Metadata.h"
#include <winsock.h>

Client::Metadata::Metadata()
{
	GetCurrentUserName();
	GetCurrentProccessInfo();
}

std::string Client::Metadata::GetCurrentUserName()
{
	char acUsername[100];
	DWORD nUserName = sizeof(acUsername);
	if (GetUserNameA(acUsername, &nUserName))
		username = acUsername;
	
	return username;
}

void Client::Metadata::GetCurrentProccessInfo()
{
	processId = GetCurrentProcessId();
}
