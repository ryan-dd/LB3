#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <ncurses.h>
#include <unordered_map>
#include "ID.h"
#include "LaserOrientation.h"
#include "Vector2d.h"
#include "Arena.h"
#include "Direction.h"
#include "GameColor.h"

class GameRenderer
{
private:
    WINDOW* window;

    // Player data
    std::unordered_map<ID, Vector2d> playerPositions;
    std::unordered_map<ID, char> playerSymbols;
    std::unordered_map<ID, LB3::GameColor> playerColor;
    std::unordered_map<ID, Vector2d> playerScorePositions;

    // Laser Data
    std::unordered_map<ID, Vector2d> lasers;
    std::unordered_map<LaserOrientation, char> laserOrientationSymbol{
        {LaserOrientation::Vertical, '|'},
        {LaserOrientation::Horizontal, '-'}
    };

    // Arena Data
    std::vector<std::vector<char>> arenaSymbols;
    char getArenaSymbol(Vector2d input);

    void initializeData(int numberOfPlayers);
    void renderArenaLocation(Vector2d location);
    void renderAllPlayers();
    void renderPlayer(ID playerID);
    void renderChar(Vector2d location, char symbol);
    void renderChar(int x, int y, char symbol);
    void renderHorizontalBorderAt(int x, int y, int length);

public:
    GameRenderer(WINDOW* window, int numberPlayers);
    void renderPlayerAppeared(ID playerID, Vector2d newPosition);
    void renderPlayerMoved(ID playerID, Vector2d newPosition);
    void renderPlayerShot(ID playerID);
    void renderPlayerTeleported(ID playerID, Vector2d newPosition);

    void renderLaserAppeared(ID laserID, Vector2d newPosition, LaserOrientation orientation);
    void renderLaserMoved(ID laserID, Vector2d newPosition, LaserOrientation orientation);
    void renderLaserRemoved(ID laserID);

    void renderArena(const Arena& arena);
    void renderSecondsLeft(int seconds);
    void renderPlayerScore(ID playerID, int score);
};

#endif // GAMERENDERER_H
