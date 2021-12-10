#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include "GameRenderer.h"
#include "Agent.h"
#include "Arena.h"
#include "MirrorType.h"

#include <cstdint>
#include <unordered_map>
#include <utility>
class GameEventHandler
{
private:
    GameRenderer& renderer;
    Arena arena;
    std::unordered_map<ID, Agent> players;
    std::unordered_map<ID, int> playersScores;

    std::unordered_map<ID, Agent> lasers;
    std::unordered_map<ID, ID> laserShotBy;
    ID currentLaserID = 0;

    std::unordered_map<Direction, LaserOrientation> directionToLaserOrientation{
        {Direction::UP, LaserOrientation::VERTICAL},
        {Direction::DOWN, LaserOrientation::VERTICAL},
        {Direction::LEFT, LaserOrientation::HORIZONTAL},
        {Direction::RIGHT, LaserOrientation::HORIZONTAL}
    };

    void updateLasers();
    Direction reflectLaser(Direction prevDirection, MirrorType mirrorType);
public:
    GameEventHandler(GameRenderer& renderer, int xMax, int yMax);
    void start();
    void step();
    void movePlayer(int playerID, Direction direction);
    void newLaser(int playerID);
    std::pair<int, int> getFinalScores();
};

#endif // GAMEEVENTHANDLER_H
