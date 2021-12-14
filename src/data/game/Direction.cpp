#include "Direction.h"
#include <stdexcept>

namespace LB3
{
Vector2d toVector(Direction direction)
{
    // Assuming origin is in upper left hand corner
    switch(direction)
    {
        case Direction::Right:
            return {1, 0};
        case Direction::Up:
            return {0, -1};
        case Direction::Left:
            return {-1, 0};
        case Direction::Down: 
            return {0, 1};
    }
}
}
