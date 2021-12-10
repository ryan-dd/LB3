#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include "GameRenderer.h"
#include "Agent.h"
#include "Arena.h"

#include <cstdint>
#include <unordered_map>

class GameEventHandler
{
private:
    GameRenderer& renderer;
    Arena arena;
    std::unordered_map<ID, Agent> players;
    std::unordered_map<ID, Vector2d> lasers;
    ID currentLaserID = 0;
public:
    GameEventHandler(GameRenderer& renderer, int xMax, int yMax);
    void start();
    void step();
    void movePlayer(int playerID, Direction direction);
    void newLaser(int playerID);
};

#endif // GAMEEVENTHANDLER_H
