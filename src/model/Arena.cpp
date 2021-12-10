#include "Arena.h"
#include "Logger.h"
#include "MirrorType.h"

Arena::Arena(int xMax, int yMax):
    xMax(xMax),
    yMax(yMax),
    xCoordinateGenerator(1, xMax-2),
    yCoordinateGenerator(1, yMax-2),
    boolGenerator(0, 1),
    randomTeleporterIndexGenerator(nullptr)
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

Vector2d Arena::getRandomTeleporterLocation(Vector2d currTeleporterPosition)
{
    if(randomTeleporterIndexGenerator == nullptr ||
       teleporters.size() == 1)
    {
        throw std::runtime_error("Arena::getRandomTeleporterLocation - Method called when there were only 0 or 1 teleporters present");
    }
    else
    {
        while(true)
        {
            auto newPosition = teleporters.at(randomTeleporterIndexGenerator->getRandomInt());
            if(currTeleporterPosition == newPosition)
            {
                continue;
            }

            return newPosition;
        }
    }
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
    if(numObstacles < 1)
    {
        Logger::log("Arena::generateObstacles - Invalid number of obstacles specified");
        return;
    }

    if(type == ObstacleType::NO_OBSTACLE || type == ObstacleType::WALL)
    {
        Logger::log("Arena::generateObstacles - Cannot generate obstacles of ObstacleType::NO_OBSTACLE or ObstacleType::WALL type");
        return;
    }

    bool isTeleporter = false;
    if(type == ObstacleType::TELEPORTER)
    {
        isTeleporter = true;
        if(numObstacles == 1)
        {
            Logger::log("Arena::generateObstacles - Must create two or more teleporters");
            return;
        }
    }

    for(int i = 0; i < numObstacles; ++i)
    {
        auto x = xCoordinateGenerator.getRandomInt();
        auto y = yCoordinateGenerator.getRandomInt();
        auto& currType = data.at(y).at(x);
        
        if(currType == ObstacleType::NO_OBSTACLE)
        {
            currType = type;
            
            if(isTeleporter)
            {
                teleporters.push_back(Vector2d(x, y));
            }
        }
        else
        {
            --i; // Another type was present, so try generating again.
        }
    }

    if(isTeleporter)
    {
        randomTeleporterIndexGenerator = std::make_unique<RandomIntGenerator>(0, teleporters.size()-1);
    }
}