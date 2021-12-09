#ifndef LIGHTPUZZLE_DIRECTION_H
#define LIGHTPUZZLE_DIRECTION_H

#include <unordered_map>
#include <cmath>

enum class Direction
{
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    NONE = 4
};

using Vector2d = std::pair<int, int>;
int toInt(Direction input);
Direction toDirection(int input);
Vector2d toVector(Direction direction);
Vector2d operator+(const Vector2d& l,const Vector2d& r);

#endif
