#include "Agent.h"
#include <algorithm>

Agent::Agent(int maxX, int maxY, int startX, int startY):
    maxX(maxX),
    maxY(maxY)
{
    xy = {startX, startY};
}

Agent::Agent(int maxX, int maxY, int startX, int startY, Direction currDirection):
    Agent(maxX, maxY, startX, startY)
{
    lastDirection = currDirection;
}

Agent::Agent()
{
}

Vector2d Agent::getXY() const
{
    return xy;
}

Direction Agent::getLastDirection() const
{
    return lastDirection;
}

bool Agent::justMovedAgainstObstacle() const
{
    return movedAgainstObstacle;
}


void Agent::requestUp()
{
    lastDirection = Direction::UP;
    
    if(--xy.second < 2)
    {
        xy.second = 1;
        movedAgainstObstacle = true;
    }
    else
    {
        movedAgainstObstacle = false;
    }
}
void Agent::requestDown()
{
    lastDirection = Direction::DOWN;
    
    if(++xy.second > maxY - 2)
    {
        xy.second = maxY - 2;
        movedAgainstObstacle = true;
    }
    else
    {
        movedAgainstObstacle = false;
    }
}
void Agent::requestLeft()
{
    lastDirection = Direction::LEFT;
    
    if(--xy.first < 2)
    {
        movedAgainstObstacle = true;
        xy.first = 1;
    }
    else
    {
        movedAgainstObstacle = false;
    }
}

void Agent::requestRight()
{
    lastDirection = Direction::RIGHT;

    if(++xy.first > maxX - 2)
    {
        movedAgainstObstacle = true;
        xy.first = maxX - 2;
    }
    else
    {
        movedAgainstObstacle = false;
    }
}