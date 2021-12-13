#ifndef PLAYERINPUTINFO_H
#define PLAYERINPUTINFO_H

#include <curses.h>

struct PlayerInputInfo
{
    char up = (char)KEY_UP;
    char down = (char)KEY_DOWN;
    char left = (char)KEY_LEFT;
    char right = (char)KEY_RIGHT;
    char laser = ' ';
};

PlayerInputInfo getPlayerOneInputInfo();
PlayerInputInfo getPlayerTwoInputInfo();
PlayerInputInfo getPlayerThreeInputInfo();

#endif // PLAYERINPUTINFO_H
