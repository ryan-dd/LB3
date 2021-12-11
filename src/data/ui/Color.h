#ifndef LB3COLOR_H
#define LB3COLOR_H

namespace LB3
{
    enum class Color
    {
        ARENA_DEFAULT = 0,
        PLAYER_DEFAULT = 1,
        PLAYER_SHOT = 2,
        PLAYER_TELEPORTED = 3,
        DISPLAY_DEFAULT = 4
    };

    int toInt(Color color);
}

#endif // LB3COLOR_H
