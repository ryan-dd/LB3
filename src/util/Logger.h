#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include "Vector2d.h"

namespace Logger
{
    void log(const std::string& message);
    void log(int number);
    void log(Vector2d position);
    void initialize();
}


#endif // LOGGER_H


