#ifndef ARENA_H
#define ARENA_H

#include <unordered_map>
#include <vector>
#include "ObstacleType.h"
#include "Vector2d.h"
#include "MirrorType.h"
#include "RandomIntGenerator.h"

class Arena
{
private:
    std::vector<std::vector<ObstacleType>> data;
    std::vector<std::vector<MirrorType>> mirrorTypes;
    void initializeData(int xMax, int yMax);
    int xMax;
    int yMax;
    RandomIntGenerator xCoordinateGenerator;
    RandomIntGenerator yCoordinateGenerator;
    RandomIntGenerator boolGenerator;

public:
    Arena(int xMax, int yMax);
    void generateObstacles(int numObstacles, ObstacleType type);
    ObstacleType at(int x, int y) const;
    ObstacleType at(Vector2d input) const;
    // MirrorType getMirrorType(Vector2d mirrorPosition);
    // MirrorType getMirrorType(int x, int y);
    int getMaxX() const;
    int getMaxY() const;
};

#endif // ARENA_H
