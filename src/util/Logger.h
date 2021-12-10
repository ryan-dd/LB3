#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace Logger
{
    void log(const std::string& message);
    void log(int number);
    void initialize();
}


#endif // LOGGER_H


