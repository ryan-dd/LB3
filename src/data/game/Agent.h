#ifndef AGENT_H
#define AGENT_H

#include <utility>
#include "Direction.h"
#include "Vector2d.h"

namespace LB3
{
struct Agent
{
    Agent(int x, int y, Direction initialDirection):
        xy(x, y),
        facingDirection(initialDirection)
    {
    }

    Agent(Vector2d xy, Direction initialDirection):
        xy(xy),
        facingDirection(initialDirection)
    {
    }
    
    Vector2d xy;
    Direction facingDirection;
};
}

#endif