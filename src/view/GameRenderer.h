#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <ncurses.h>
#include <unordered_map>
#include "ID.h"
#include "LaserOrientation.h"
#include "Vector2d.h"
#include "Arena.h"

class GameRenderer
{
private:
    WINDOW* window;
    std::unordered_map<ID, Vector2d> playerPositions;
    std::unordered_map<ID, char> playerSymbols;
    std::unordered_map<ID, Vector2d> lasers;
    std::unordered_map<LaserOrientation, char> LaserOrientationSymbol{
        {LaserOrientation::VERTICAL, '|'},
        {LaserOrientation::HORIZONTAL, '-'}
    };

public:
    GameRenderer(WINDOW* window);
    void renderArena(const Arena& arena);
    void renderPlayerFirstTime(int playerID, Vector2d newPosition);
    void renderPlayer(int playerID, Vector2d newPosition);

    void renderLaserFirstTime(int laserID, Vector2d newPosition, LaserOrientation orientation);
    void renderLaser(int laserID, Vector2d newPosition, LaserOrientation orientation);
    void removeLaser(int laserID);
};




#endif // GAMERENDERER_H
