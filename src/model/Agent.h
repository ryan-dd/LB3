#ifndef AGENT_H
#define AGENT_H

#include <utility>
#include "Direction.h"
#include "Vector2d.h"

struct Agent
{
    Agent(int x, int y, Direction initialDirection):
        xy(x, y),
        facingDirection(initialDirection)
    {
    }
    
    Vector2d xy;
    Direction facingDirection;
};

#endif