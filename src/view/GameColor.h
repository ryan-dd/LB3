#ifndef GAMECOLOR_H
#define GAMECOLOR_H

enum class GameColor
{
    ARENA_DEFAULT,
    PLAYER_DEFAULT,
    PLAYER_SHOT,
    PLAYER_TELEPORTED,
    DISPLAY_DEFAULT
};

int toInt(GameColor color)
{
    return static_cast<int>(color);
}

#endif // GAMECOLOR_H
