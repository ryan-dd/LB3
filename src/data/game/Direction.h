#ifndef DIRECTION_H
#define DIRECTION_H

#include <cmath>
#include "Vector2d.h"

enum class Direction
{
    Right,
    Up,
    Left,
    Down
};

Vector2d toVector(Direction direction);

#endif
