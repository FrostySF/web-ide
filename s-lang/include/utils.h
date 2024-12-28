#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <tchar.h>
#include <strsafe.h>
#include <fstream>

namespace utils
{
    void crossplatform_exec(std::string cmd);
};

#endif // UTILS_H
