#include "Agent.h"
#include <algorithm>

Agent::Agent(int maxX, int maxY, int startX, int startY):
    maxX(maxX),
    maxY(maxY)
{
    xy = {startX, startY};
}

Agent::Agent()
{
}

const std::pair<int, int>& Agent::getXY()
{
    return xy;
}

void Agent::requestUp()
{
    if(--xy.second < 2)
    {
        xy.second = 1;
    }
}
void Agent::requestDown()
{
    if(++xy.second > maxY - 2)
    {
        xy.second = maxY - 2;
    }
}
void Agent::requestLeft()
{
    if(--xy.first < 2)
    {
        xy.first = 1;
    }
}
void Agent::requestRight()
{
    if(++xy.first > maxX - 2)
    {
        xy.first = maxX - 2;
    }
}
