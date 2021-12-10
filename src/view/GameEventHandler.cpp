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
    playersScores.insert({0, 0});
    playersScores.insert({1, 0});

    renderer.renderPlayerFirstTime(0, players.at(0).xy);
    renderer.renderPlayerFirstTime(1, players.at(1).xy);
}

void GameEventHandler::step()
{
    updateLasers();
}

void GameEventHandler::updateLasers()
{
    auto itr = lasers.begin();
    while (itr != lasers.end())
    {
        auto& laser = itr->second;
        auto newLaserPosition = laser.xy + toVector(laser.facingDirection);
        if(arena.at(newLaserPosition.x, newLaserPosition.y) == ObstacleType::NO_OBSTACLE)
        {
            laser.xy = newLaserPosition;
            
            if(players.at(0).xy == newLaserPosition)
            {
                auto& otherPlayerScore = playersScores.at(1);
                ++otherPlayerScore;
                renderer.renderPlayerScore(1, otherPlayerScore);
                renderer.removeLaser(itr->first);
                itr = lasers.erase(itr);
                continue;
            }

            if(players.at(1).xy == newLaserPosition)
            {
                auto& otherPlayerScore = playersScores.at(0);
                ++otherPlayerScore;
                renderer.renderPlayerScore(0, otherPlayerScore);
                renderer.removeLaser(itr->first);
                itr = lasers.erase(itr);
                continue;
            }

            renderer.renderLaser(itr->first, 
                                 newLaserPosition,
                                 directionToLaserOrientation.at(laser.facingDirection));
            ++itr;
        }
        else
        {
            renderer.removeLaser(itr->first);
            itr = lasers.erase(itr);
        }
    }
}

void GameEventHandler::movePlayer(int playerID, Direction direction)
{
    auto& player = players.at(playerID);
    player.facingDirection = direction;

    auto newPlayerPosition = player.xy + toVector(direction);

    if(arena.at(newPlayerPosition.x, newPlayerPosition.y) == ObstacleType::NO_OBSTACLE)
    {
        player.xy = newPlayerPosition;
        renderer.renderPlayer(playerID, newPlayerPosition);
    }
}

void GameEventHandler::newLaser(int playerID)
{
    auto& player = players.at(playerID);
    auto direction = player.facingDirection;
    Vector2d newLaserPosition = player.xy + toVector(direction);

    if(arena.at(newLaserPosition.x, newLaserPosition.y) == ObstacleType::NO_OBSTACLE)
    {
        Agent newLaser(newLaserPosition, direction);
        ++currentLaserID;
        lasers.emplace(currentLaserID, newLaser);
        renderer.renderLaserFirstTime(currentLaserID, 
                                      newLaserPosition,
                                      directionToLaserOrientation.at(direction));
    }
}