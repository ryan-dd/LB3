#ifndef ARENA_H
#define ARENA_H

#include "ObstacleType.h"
#include <vector>
#include "Vector2d.h"

class Arena
{
private:
    std::vector<std::vector<ObstacleType>> data;
    void initializeData(int xMax, int yMax);
    int xMax;
    int yMax;
public:
    Arena(int xMax, int yMax);
    void generateObstacles(int numObstacles);
    ObstacleType at(int x, int y) const;
    ObstacleType at(Vector2d input) const;
    int getXmax() const;
    int getYmax() const;
};

#endif // ARENA_H
