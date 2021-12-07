#include "Direction.h"

namespace lightpuzzle
{
    int toInt(Direction input)
    {
        return static_cast<int>(input);
    }

    Direction toDirection(int input)
    {
        return static_cast<Direction>(input);
    }

    Eigen::Vector2d toVector(Direction direction)
    {
        switch(direction)
        {
            case Direction::RIGHT:
                return {1, 0};
            case Direction::UP_RIGHT:
                return {sqrt2over2, sqrt2over2};
            case Direction::UP:
                return {0, 1};
            case Direction::UP_LEFT:
                return {-sqrt2over2, sqrt2over2};
            case Direction::LEFT:
                return {-1, 0};
            case Direction::DOWN_LEFT:
                return {-sqrt2over2, -sqrt2over2};
            case Direction::DOWN:
                return {0, -1};
            case Direction::DOWN_RIGHT:
                return {sqrt2over2, -sqrt2over2};
            case Direction::NONE:
                return {0, 0};
        }
    }

    Direction getNormal(Direction input)
    {
        return toDirection((toInt(input) + 2) % 8);
    }
}
