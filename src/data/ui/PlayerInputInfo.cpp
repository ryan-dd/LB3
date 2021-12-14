#include "PlayerInputInfo.h"

namespace LB3
{
PlayerInputInfo getPlayerOneInputInfo()
{
    return PlayerInputInfo();
}

PlayerInputInfo getPlayerTwoInputInfo()
{
    PlayerInputInfo info;
    info.up = 'w';
    info.down = 's';
    info.left = 'a';
    info.right = 'd';
    info.laser = 'v';
    return info;
}

PlayerInputInfo getPlayerThreeInputInfo()
{
    PlayerInputInfo info;
    info.up = 'k';
    info.down = 'j';
    info.left = 'h';
    info.right = 'l';
    info.laser = 'i';
    return info;
}
}
