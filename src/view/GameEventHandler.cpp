#include "GameEventHandler.h"
#include <iostream>
#include <fstream>
#include <Logger.h>

GameEventHandler::GameEventHandler(GameRenderer& renderer, int xMax, int yMax):
    renderer(renderer),
    arena(xMax, yMax)
{
    arena.generateObstacles(30, ObstacleType::FORWARD_MIRROR);
    arena.generateObstacles(30, ObstacleType::BACK_MIRROR);
}

void GameEventHandler::start()
{   
    renderer.renderArena(arena);
    renderer.renderPlayerScore(0, 0);
    renderer.renderPlayerScore(1, 0);
    players.insert({0, Agent(arena.getMaxX()-2, arena.getMaxY()-2, Direction::LEFT)});
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
        auto typeAtNewPosition = arena.at(newLaserPosition);
        if(typeAtNewPosition == ObstacleType::NO_OBSTACLE)
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
        else if(typeAtNewPosition == ObstacleType::FORWARD_MIRROR)
        {
            laser.xy = newLaserPosition;
            laser.facingDirection = reflectLaser(laser.facingDirection, MirrorType::FORWARD);
        }
        else if(typeAtNewPosition == ObstacleType::BACK_MIRROR)
        {
            laser.xy = newLaserPosition;
            laser.facingDirection = reflectLaser(laser.facingDirection, MirrorType::BACK);
        }
        else
        {
            renderer.removeLaser(itr->first);
            itr = lasers.erase(itr);
        }
    }
}

Direction GameEventHandler::reflectLaser(Direction prevDirection, MirrorType mirrorType)
{
    if(mirrorType == MirrorType::FORWARD)
    {
        switch (prevDirection)
        {
        case Direction::RIGHT:
            return Direction::UP;
            break;
        case Direction::UP:
            return Direction::RIGHT;
            break;
        case Direction::DOWN:
            return Direction::LEFT;
            break;
        case Direction::LEFT:
            return Direction::DOWN;
            break;
        }
    }
    else
    {
        switch(prevDirection)
        {
        case Direction::RIGHT:
            return Direction::DOWN;
            break;
        case Direction::DOWN:
            return Direction::RIGHT;
            break;
        case Direction::LEFT:
            return Direction::UP;
            break;
        case Direction::UP:
            return Direction::LEFT;
            break;
        }
        
    }
}

void GameEventHandler::movePlayer(int playerID, Direction direction)
{
    auto& player = players.at(playerID);
    player.facingDirection = direction;

    auto newPlayerPosition = player.xy + toVector(direction);

    if(arena.at(newPlayerPosition) == ObstacleType::NO_OBSTACLE)
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

    auto obstacleType = arena.at(newLaserPosition);
    if(obstacleType == ObstacleType::NO_OBSTACLE ||
       obstacleType == ObstacleType::FORWARD_MIRROR ||
       obstacleType == ObstacleType::BACK_MIRROR)
    {
        if(obstacleType == ObstacleType::FORWARD_MIRROR)
        {
            direction = reflectLaser(direction, MirrorType::FORWARD);
        }
        else if(obstacleType == ObstacleType::BACK_MIRROR)
        {
            direction = reflectLaser(direction, MirrorType::BACK);
        }

        Agent newLaser(newLaserPosition, direction);
        ++currentLaserID;
        lasers.emplace(currentLaserID, newLaser);
        Logger::log("Got to rendering");

        renderer.renderLaserFirstTime(
            currentLaserID, 
            newLaserPosition,
            directionToLaserOrientation.at(direction));
    }
}

std::pair<int, int> GameEventHandler::getFinalScores()
{
    return {playersScores.at(0), playersScores.at(1)};
}