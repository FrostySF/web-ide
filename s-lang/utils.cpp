#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void utils::crossplatform_exec(std::string cmd)
{
#ifdef _WIN32
    //yeah simple as possible
    std::ofstream f("start.bat");
    f << cmd;
    f.close();
    system("start start.bat");
#else
    std::string terminalCommand;

    // Check for common terminal emulators
    if (system("which gnome-terminal > /dev/null 2>&1") == 0) {
        terminalCommand = "gnome-terminal -- bash -c '" + cmd + "'";
    } else if (system("which xterm > /dev/null 2>&1") == 0) {
        terminalCommand = "xterm -e bash -c '" + cmd + "'";
    } else if (system("which konsole > /dev/null 2>&1") == 0) {
        terminalCommand = "konsole -e bash -c '" + cmd + "'";
    } else {
        std::cerr << "No supported terminal emulator found." << std::endl;
        return;
    }

    if (system(terminalCommand.c_str()) != 0) {
        std::cerr << "Failed to open new terminal window." << std::endl;
    }
#endif
}
