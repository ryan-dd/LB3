#ifndef DIRECTION_H
#define DIRECTION_H

#include <cmath>
#include "Vector2d.h"

enum class Direction
{
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3
};

Vector2d toVector(Direction direction);
int toInt(Direction direction);

#endif
