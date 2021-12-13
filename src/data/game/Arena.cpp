#include "Arena.h"
#include "Logger.h"
#include "MirrorType.h"

#include <algorithm>

Arena::Arena(int xMax, int yMax, std::vector<Vector2d> noObstaclePositions):
    xMax(xMax),
    yMax(yMax),
    availablePositions((xMax - 2) * (yMax - 2) - noObstaclePositions.size()),
    xCoordinateGenerator(1, xMax-2),
    yCoordinateGenerator(1, yMax-2),
    boolGenerator(0, 1),
    randomTeleporterIndexGenerator(std::nullopt),
    noObstaclePositions(noObstaclePositions)
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
    for(size_t rowIndex = 0; rowIndex < data.size(); ++rowIndex)
    {
        if(rowIndex == 0 || rowIndex == data.size() - 1)
        {
            data.at(rowIndex) = std::vector<ObstacleType>(xMax, ObstacleType::WALL);
        }
        else
        {
            data.at(rowIndex) = std::vector<ObstacleType>(xMax, ObstacleType::NO_OBSTACLE);
            data.at(rowIndex).at(0) = ObstacleType::WALL;
            data.at(rowIndex).at(xMax - 1) = ObstacleType::WALL;
        }
    }
}

void Arena::generateObstacles(ObstacleType type, int numObstacles)
{
    if(numObstacles < 1)
    {
        throw std::invalid_argument("Arena::generateObstacles - Invalid number of obstacles specified");
    }

    if(type == ObstacleType::NO_OBSTACLE || type == ObstacleType::WALL)
    {
        throw std::invalid_argument("Arena::generateObstacles - Cannot generate obstacles of ObstacleType::NO_OBSTACLE or ObstacleType::WALL type");
    }

    if(availablePositions - numObstacles < 0)
    {
        throw std::invalid_argument("Arena::generateObstacles - Not enough available positions to generate obstacles");
    }

    bool isTeleporter = false;
    if(type == ObstacleType::TELEPORTER)
    {
        isTeleporter = true;

        if(numObstacles == 1)
        {
            throw std::invalid_argument("Arena::generateObstacles - Must create two or more teleporters");
        }
    }

    for(int i = 0; i < numObstacles; ++i)
    {
        auto x = xCoordinateGenerator.getRandomInt();
        auto y = yCoordinateGenerator.getRandomInt();
        auto& currType = data.at(y).at(x);
        
        if(!canPlaceObstacle(x, y, currType))
        {
            --i;
            continue;
        }
        else
        {
            currType = type;
            --availablePositions;
            
            if(isTeleporter)
            {
                teleporters.push_back(Vector2d(x, y));
            }
        }
    }

    if(isTeleporter)
    {
        randomTeleporterIndexGenerator.emplace(0, teleporters.size()-1);
    }
}

bool Arena::canPlaceObstacle(int x, int y, ObstacleType currType)
{
    auto startIt = noObstaclePositions.begin();
    auto endIt = noObstaclePositions.end();
    
    if(std::find(startIt, endIt, Vector2d(x, y)) != endIt)
    {
        return false;
    }

    if(currType != ObstacleType::NO_OBSTACLE)
    {
        return false;
    }

    return true;
}


Vector2d Arena::getRandomTeleporterLocation(Vector2d currTeleporterPosition) const
{
    if(!randomTeleporterIndexGenerator.has_value() ||
        teleporters.size() < 2)
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
