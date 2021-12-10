#include "Logger.h"
#include <fstream>
namespace Logger
{
    void log(const std::string& message)
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ios_base::app);
        outfile << message << '\n'; 
    }

    void log(int number)
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ios_base::app);
        outfile << number << '\n'; 
    }

    void log(Vector2d position)
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ios_base::app);
        outfile << "Position: " << position.x << " " << position.y << '\n'; 
    }

    void initialize()
    {
        std::ofstream outfile;
        outfile.open("log.txt", std::ofstream::out | std::ofstream::trunc);
    }
}




