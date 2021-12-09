#ifndef AGENT_H
#define AGENT_H

#include <utility>
#include "Direction.h"

class Agent
{
private:
    std::pair<int, int> xy{1, 1};
    int maxX;
    int maxY;
    Direction lastDirection = Direction::NONE;
    bool movedAgainstObstacle = false;
    
public:
    Agent(int maxX, int maxY, int startX, int startY);
    Agent(int maxX, int maxY, int startX, int startY, Direction currDirection);
    Agent();
    Vector2d getXY() const;
    Direction getLastDirection() const;
    bool justMovedAgainstObstacle() const;
    void requestUp();
    void requestDown();
    void requestLeft();
    void requestRight();
};



#endif