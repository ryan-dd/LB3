#ifndef AGENT_H
#define AGENT_H

#include <utility>

class Agent
{
private:
    std::pair<int, int> xy{1, 1};
    int maxX;
    int maxY;
    
public:
    Agent(int maxX, int maxY, int startX, int startY);
    Agent();
    const std::pair<int, int>& getXY();
    void requestUp();
    void requestDown();
    void requestLeft();
    void requestRight();
};



#endif