#include "GameEventHandler.h"
#include <iostream>
#include <fstream>

GameEventHandler::GameEventHandler(GameRenderer& renderer, int xMax, int yMax):
    renderer(renderer),
    arena(xMax, yMax)
{
    arena.generateObstacles(50);
}

void GameEventHandler::start()
{   
    renderer.renderArena(arena);
    players.insert({0, Agent(3, 3, Direction::LEFT)});
    players.insert({1, Agent(1, 1, Direction::RIGHT)});

    renderer.renderPlayerFirstTime(0, players.at(0).xy);
    renderer.renderPlayerFirstTime(1, players.at(1).xy);
}

void GameEventHandler::step()
{

}

void GameEventHandler::movePlayer(int playerID, Direction direction)
{
    auto& player = players.at(playerID);
    player.facingDirection = direction;

    auto newPlayerPosition = player.xy + toVector(direction);

    if(arena.at(newPlayerPosition.x, newPlayerPosition.y) == ObstacleType::EMPTY)
    {
        player.xy = newPlayerPosition;
        renderer.renderPlayer(playerID, newPlayerPosition);
    }
}

void GameEventHandler::newLaser(int playerID)
{
    
}