#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <ncurses.h>
#include <unordered_map>
#include "ID.h"
#include "LaserOrientation.h"
#include "Vector2d.h"
#include "Arena.h"
#include "Direction.h"
class GameRenderer
{
private:
    WINDOW* window;

    // Player data
    std::unordered_map<ID, Vector2d> playerPositions;
    std::unordered_map<ID, char> playerSymbols;
    std::unordered_map<ID, Vector2d> playerScorePositions;

    // Laser Data
    std::unordered_map<ID, Vector2d> lasers;
    std::unordered_map<LaserOrientation, char> laserOrientationSymbol{
        {LaserOrientation::VERTICAL, '|'},
        {LaserOrientation::HORIZONTAL, '-'}
    };

    // Arena Data
    std::vector<std::vector<char>> arenaSymbols;
    char getArenaSymbol(Vector2d input);

    void reRerenderArenaLocation(Vector2d location);
    void reRenderAllPlayers();
    void reRenderPlayer(ID playerID);

    inline void renderChar(Vector2d location, char symbol)
    {
        mvwaddch(window, location.y, location.x, symbol);
    }

    inline void renderChar(int x, int y, char symbol)
    {
        mvwaddch(window, y, x, symbol);
    }

public:
    GameRenderer(WINDOW* window);
    void renderArena(const Arena& arena);
    void renderSecondsLeft(int seconds);
    
    void renderPlayerFirstTime(ID playerID, Vector2d newPosition);
    void renderPlayer(ID playerID, Vector2d newPosition);
    void renderPlayerScore(ID playerID, int score);

    void renderLaserFirstTime(
        ID laserID, 
        Vector2d newPosition, 
        LaserOrientation orientation);
    void renderLaser(ID laserID, Vector2d newPosition, LaserOrientation orientation);
    void removeLaser(ID laserID);
};




#endif // GAMERENDERER_H
