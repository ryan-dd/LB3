#include "ArenaCoordinateGenerator.h"

ArenaCoordinateGenerator::ArenaCoordinateGenerator(int xMax, int yMax):
    xCoordinateGenerator(1, xMax-2),
    yCoordinateGenerator(1, yMax-2)
{
}

Vector2d ArenaCoordinateGenerator::getRandomCoords()
{
    auto x = xCoordinateGenerator.getRandomInt();
    auto y = yCoordinateGenerator.getRandomInt();
    return Vector2d(x, y);
}