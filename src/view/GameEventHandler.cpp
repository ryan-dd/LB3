#include "GameEventHandler.h"
#include "RandomIntGenerator.h"
#include <iostream>
#include <fstream>
#include <Logger.h>

GameEventHandler::GameEventHandler(
    GameRenderer& renderer, 
    GameStartParameters parameters):
        renderer(renderer),
        arena(parameters.arena)
{
    RandomIntGenerator directionGenerator(0, 3);
    for (int playerID = 0; playerID < parameters.getNumberOfPlayers(); playerID++)
    {
        players.insert({playerID, parameters.agents.at(playerID)});
        playersScores.insert({playerID, 0});
    }
}

void GameEventHandler::start()
{   
    renderer.renderArena(arena);
    for(int playerID = 0; playerID < players.size(); ++ playerID)
    {
        renderer.renderPlayerScore(playerID, 0);
        renderer.renderPlayerAppeared(playerID, players.at(playerID).xy);
    }
}

void GameEventHandler::step()
{
    updateLasers();
}

void GameEventHandler::movePlayer(int playerID, Direction direction)
{
    auto& player = players.at(playerID);
    player.facingDirection = direction;

    auto newPlayerPosition = player.xy + toVector(direction);
    auto obstacleType = arena.at(newPlayerPosition);
    
    if(obstacleType == ObstacleType::NO_OBSTACLE)
    {
        player.xy = newPlayerPosition;
        renderer.renderPlayerMoved(playerID, player.xy);
    }
    else if(obstacleType == ObstacleType::TELEPORTER)
    {
        player.xy = arena.getRandomTeleporterLocation(newPlayerPosition);
        renderer.renderPlayerTeleported(playerID, player.xy);
    }
}

void GameEventHandler::newLaser(int playerID)
{
    auto& player = players.at(playerID);
    auto direction = player.facingDirection;
    Vector2d newLaserPosition = player.xy + toVector(direction);

    auto obstacleType = arena.at(newLaserPosition);
    if(obstacleType == ObstacleType::NO_OBSTACLE ||
       obstacleType == ObstacleType::TELEPORTER ||
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
        laserShotBy.emplace(currentLaserID, playerID);

        renderer.renderLaserAppeared(
            currentLaserID, 
            newLaserPosition,
            directionToLaserOrientation.at(direction));
    }
}

void GameEventHandler::updateLasers()
{
    auto itr = lasers.begin();
    while (itr != lasers.end())
    {
        auto& laser = itr->second;
        auto newLaserPosition = laser.xy + toVector(laser.facingDirection);
        auto typeAtNewPosition = arena.at(newLaserPosition);
        
        if(typeAtNewPosition == ObstacleType::NO_OBSTACLE ||
           typeAtNewPosition == ObstacleType::TELEPORTER)
        {
            laser.xy = newLaserPosition;
            bool playerHit = false;
            for(int playerID = 0; playerID < players.size(); ++playerID)
            {
                auto player = players.at(playerID);
                if(player.xy == newLaserPosition)
                {
                    auto origPlayerID = laserShotBy.at(itr->first);
                    auto& origPlayerScore = playersScores.at(origPlayerID);
                    if(origPlayerID == playerID)
                    {
                        --origPlayerScore;
                    }
                    else
                    {
                        ++origPlayerScore;
                    }
                    
                    renderer.renderPlayerScore(origPlayerID, origPlayerScore);
                    renderer.renderPlayerShot(playerID);
                    playerHit = true;
                }
            }

            if(playerHit)
            {
                renderer.renderLaserRemoved(itr->first);
                laserShotBy.erase(itr->first);
                itr = lasers.erase(itr);
            }
            else
            {
                renderer.renderLaserMoved(itr->first, 
                                 newLaserPosition,
                                 directionToLaserOrientation.at(laser.facingDirection));
                ++itr;
            }
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
            renderer.renderLaserRemoved(itr->first);
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

std::pair<int, int> GameEventHandler::getFinalScores()
{
    return {playersScores.at(0), playersScores.at(1)};
}
