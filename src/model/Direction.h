#ifndef LIGHTPUZZLE_DIRECTION_H
#define LIGHTPUZZLE_DIRECTION_H

#include <unordered_map>
#include <cmath>
#include <Eigen/Dense>

namespace lightpuzzle
{
    /**
     * @brief Enum representing direction as a vector
     * 
     */
    enum class Direction
    {
        RIGHT = 0,
        DOWN_RIGHT = 1,
        DOWN = 2,
        DOWN_LEFT = 3,
        LEFT = 4,
        UP_LEFT = 5,
        UP = 6,
        UP_RIGHT = 7,
        NONE = 8
    };

    inline static double sqrt2over2 = std::sqrt(2)/2;
    int toInt(Direction input);
    Direction toDirection(int input);
    Direction getNormal(Direction input);
    Eigen::Vector2d toVector(Direction direction);
}

#endif
