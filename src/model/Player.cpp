#include "Player.h"
#include <algorithm>

Player::Player(int maxX, int maxY):
    maxX(maxX),
    maxY(maxY)
{
}

Player::Player()
{
}

const std::pair<int, int>& Player::getXY()
{
    return xy;
}

void Player::requestUp()
{
    if(--xy.second < 2)
    {
        xy.second = 1;
    }
}
void Player::requestDown()
{
    if(++xy.second > maxY - 2)
    {
        xy.second = maxY - 2;
    }
}
void Player::requestLeft()
{
    if(--xy.first < 2)
    {
        xy.first = 1;
    }
}
void Player::requestRight()
{
    if(++xy.first > maxX - 2)
    {
        xy.first = maxX - 2;
    }
}
