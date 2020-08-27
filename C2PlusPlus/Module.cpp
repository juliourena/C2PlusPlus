#include "Module.h"

namespace C2PlusPlus
{
    std::string Module::Cmd(std::string command)
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
}