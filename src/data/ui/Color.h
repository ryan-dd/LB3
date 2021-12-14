#ifndef LB3COLOR_H
#define LB3COLOR_H

namespace LB3
{
    enum class Color
    {
        ArenaDefault = 0,
        PlayerDefault = 1,
        PlayerShot = 2,
        PlayerTeleported = 3,
        DisplayDefault = 4
    };

    int toInt(Color color);
}

#endif // LB3COLOR_H
