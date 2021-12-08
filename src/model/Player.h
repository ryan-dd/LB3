#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class Player
{
private:
    std::pair<int, int> xy{1, 1};
    int maxX;
    int maxY;
    
public:
    Player(int maxX, int maxY);
    Player();
    const std::pair<int, int>& getXY();
    void requestUp();
    void requestDown();
    void requestLeft();
    void requestRight();
};



#endif