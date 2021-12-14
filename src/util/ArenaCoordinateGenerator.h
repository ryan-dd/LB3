#ifndef ARENACOORDINATEGENERATOR_H
#define ARENACOORDINATEGENERATOR_H

#include "RandomIntGenerator.h"
#include "Vector2d.h"

namespace LB3
{
class ArenaCoordinateGenerator
{
private:
    RandomIntGenerator xCoordinateGenerator;
    RandomIntGenerator yCoordinateGenerator;
public:
    ArenaCoordinateGenerator(int xMax, int yMax);
    Vector2d getRandomCoords();
};
}

#endif // ARENACOORDINATEGENERATOR_H
