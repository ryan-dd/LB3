#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#include <fstream>
#include <string>

namespace DebugLogger
{
    void log(const std::string& message)
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ios_base::app);
        outfile << message << '\n'; 
    }
}


#endif // DEBUGLOGGER_H


