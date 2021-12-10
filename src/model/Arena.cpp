#include "Arena.h"
#include "Logger.h"
#include "MirrorType.h"

Arena::Arena(int xMax, int yMax):
    xMax(xMax),
    yMax(yMax),
    xCoordinateGenerator(1, xMax-2),
    yCoordinateGenerator(1, yMax-2),
    boolGenerator(0, 1)
{
    initializeData(xMax, yMax);
}

int Arena::getMaxX() const
{
    return xMax;
}

int Arena::getMaxY() const
{
    return yMax;
}

ObstacleType Arena::at(int x, int y) const
{
    return data.at(y).at(x);
}

ObstacleType Arena::at(Vector2d input) const
{
    return data.at(input.y).at(input.x);
}

void Arena::initializeData(int xMax, int yMax)
{
    data.resize(yMax);
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(i == 0 || i == data.size() - 1)
        {
            data.at(i) = std::vector<ObstacleType>(xMax, ObstacleType::WALL);
        }
        else
        {
            data.at(i) = std::vector<ObstacleType>(xMax, ObstacleType::NO_OBSTACLE);
            data.at(i).at(0) = ObstacleType::WALL;
            data.at(i).at(xMax - 1) = ObstacleType::WALL;
        }
    }
}

void Arena::generateObstacles(int numObstacles, ObstacleType type)
{
    if(type == ObstacleType::NO_OBSTACLE || type == ObstacleType::WALL)
    {
        Logger::log("Arena::generateObstacles - Cannot generate obstacles of ObstacleType::NO_OBSTACLE or ObstacleType::WALL type");
        return;
    }

    for(int i = 0; i < numObstacles; ++i)
    {
        auto x = xCoordinateGenerator.getRandomInt();
        auto y = yCoordinateGenerator.getRandomInt();
        auto& currType = data.at(y).at(x);
        
        if(currType == ObstacleType::NO_OBSTACLE)
        {
            currType = type;
        }
        else
        {
            --i; // Another type was present, so try generating again.
        }
    }
}