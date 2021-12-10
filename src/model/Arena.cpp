#include "Arena.h"
#include <random>

Arena::Arena(int xMax, int yMax):
    xMax(xMax),
    yMax(yMax)
{
    initializeData(xMax, yMax);
}

int Arena::getXmax() const
{
    return xMax;
}

int Arena::getYmax() const
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
    // Initialize walls, map, and obstacles.
    data.resize(yMax);
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(i == 0 || i == data.size() - 1)
        {
            data.at(i) = std::vector<ObstacleType>(xMax, ObstacleType::WALL);
        }
        else
        {
            data.at(i) = std::vector<ObstacleType>(xMax, ObstacleType::EMPTY);
            data.at(i).at(0) = ObstacleType::WALL;
            data.at(i).at(xMax - 1) = ObstacleType::WALL;
        }
    }
}

void Arena::generateObstacles(int numObstacles)
{
    int yMax = data.size();
    int xMax = data[0].size();

    // Generate obstacles
    std::mt19937 xRng(std::random_device{}());
    std::mt19937 yRng(std::random_device{}());
    std::uniform_int_distribution<int> yDistribution(1, yMax-2);
    std::uniform_int_distribution<int> xDistribution(1, xMax-2);

    for(int i = 0; i < numObstacles; ++i)
    {
        auto x = xDistribution(xRng);
        auto y = yDistribution(yRng);
        data.at(y).at(x) = ObstacleType::OBSTACLE;
    }
}