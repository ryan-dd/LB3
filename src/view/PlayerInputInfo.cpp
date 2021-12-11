#include "PlayerInputInfo.h"

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
