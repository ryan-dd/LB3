#include "Direction.h"
#include <stdexcept>

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

int toInt(Direction direction)
{
    return static_cast<int>(direction);
}

Direction toDirection(int input)
{
    if(input < 0 || input > 3)
    {
        throw std::invalid_argument("toDirection - input was not between 0 and 3");
    }
    
    return static_cast<Direction>(input);
}
