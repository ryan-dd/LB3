#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <utility>

struct Vector2d
{
    Vector2d(): x(0), y(0)
    {

    }

    Vector2d(int x, int y): x(x), y(y)
    {

    }

    int x;
    int y;
};

inline Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};                                    
}  

#endif // VECTOR2D_H