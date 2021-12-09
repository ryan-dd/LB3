#include "Direction.h"

int toInt(Direction input)
{
    return static_cast<int>(input);
}

Direction toDirection(int input)
{
    return static_cast<Direction>(input);
}

Vector2d toVector(Direction direction)
{
    switch(direction)
    {
        case Direction::RIGHT:
            return {1, 0};
        case Direction::UP:
            return {0, 1};
        case Direction::LEFT:
            return {-1, 0};
        case Direction::DOWN:
            return {0, -1};
        case Direction::NONE:
            return {0, 0};
    }
}

Vector2d operator+(const Vector2d& l,const Vector2d& r) 
{   
    return {l.first+r.first, l.second+r.second};                                    
}  

