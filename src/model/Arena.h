#ifndef ARENA_H
#define ARENA_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>

#include "ObstacleType.h"
#include "Vector2d.h"
#include "MirrorType.h"
#include "RandomIntGenerator.h"

class Arena
{
private:
    std::vector<std::vector<ObstacleType>> data;
    std::vector<Vector2d> teleporters;
    void initializeData(int xMax, int yMax);
    int xMax;
    int yMax;
    RandomIntGenerator xCoordinateGenerator;
    RandomIntGenerator yCoordinateGenerator;
    RandomIntGenerator boolGenerator;
    mutable std::optional<RandomIntGenerator> randomTeleporterIndexGenerator;

public:
    Arena(int xMax, int yMax);
    void generateObstacles(ObstacleType type, int numObstacles);
    ObstacleType at(int x, int y) const;
    ObstacleType at(Vector2d input) const;
    int getMaxX() const;
    int getMaxY() const;
    Vector2d getRandomTeleporterLocation(Vector2d currTeleporterPosition) const;
};

#endif // ARENA_H
