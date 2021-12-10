#include "Direction.h"

Vector2d toVector(Direction direction)
{
    // Assuming origin is in upper left hand corner
    switch(direction)
    {
        case Direction::RIGHT:
            return {1, 0};
        case Direction::UP:
            return {0, -1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::DOWN: 
            return {0, 1};
    }
}
