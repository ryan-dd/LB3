#include "GameEventHandler.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Logger.h>

GameEventHandler::GameEventHandler(
    GameRenderer& renderer, 
    GameStartParameters parameters):
        renderer(renderer),
        arena(parameters.arena)
{
    for (int playerID = 0; playerID < parameters.getNumberOfPlayers(); playerID++)
    {
        players.insert({playerID, parameters.players.at(playerID)});
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
    
    if(obstacleType == ObstacleType::NoObstacle)
    {
        player.xy = newPlayerPosition;
        renderer.renderPlayerMoved(playerID, player.xy);
    }
    else if(obstacleType == ObstacleType::Teleporter)
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
    if(obstacleType == ObstacleType::NoObstacle ||
       obstacleType == ObstacleType::Teleporter ||
       obstacleType == ObstacleType::ForwardMirror ||
       obstacleType == ObstacleType::BackMirror)
    {
        if(obstacleType == ObstacleType::ForwardMirror)
        {
            direction = reflectLaser(direction, MirrorType::Forward);
        }
        else if(obstacleType == ObstacleType::BackMirror)
        {
            direction = reflectLaser(direction, MirrorType::Back);
        }

        Agent newLaser(newLaserPosition, direction);
        ++currentLaserID;
        lasers.emplace(currentLaserID, newLaser);
        laserShotBy.emplace(currentLaserID, playerID);
        
        bool atLeastOnePlayerHit = updatePlayersAtLaserPosition(currentLaserID);
        if(atLeastOnePlayerHit)
        {
            laserShotBy.erase(currentLaserID);
            lasers.erase(currentLaserID);
        }
        else
        {
            renderer.renderLaserAppeared(
            currentLaserID, 
            newLaserPosition,
            directionToLaserOrientation.at(direction));
        }
    }
}

void GameEventHandler::updateLasers()
{
    auto itr = lasers.begin();
    while (itr != lasers.end())
    {
        auto laserID = itr->first;
        auto& laser = itr->second;
        auto newLaserPosition = laser.xy + toVector(laser.facingDirection);
        auto obstacleAtNewPosition = arena.at(newLaserPosition);
        
        if(obstacleAtNewPosition == ObstacleType::NoObstacle ||
           obstacleAtNewPosition == ObstacleType::Teleporter)
        {
            laser.xy = newLaserPosition;
            bool atLeastOnePlayerHit = updatePlayersAtLaserPosition(laserID);
            
            if(atLeastOnePlayerHit)
            {
                renderer.renderLaserRemoved(laserID);
                laserShotBy.erase(laserID);
                itr = lasers.erase(itr);
            }
            else
            {
                renderer.renderLaserMoved(laserID, 
                                 newLaserPosition,
                                 directionToLaserOrientation.at(laser.facingDirection));
                ++itr;
            }
        }
        else if(obstacleAtNewPosition == ObstacleType::ForwardMirror)
        {
            laser.xy = newLaserPosition;
            laser.facingDirection = reflectLaser(laser.facingDirection, MirrorType::Forward);
        }
        else if(obstacleAtNewPosition == ObstacleType::BackMirror)
        {
            laser.xy = newLaserPosition;
            laser.facingDirection = reflectLaser(laser.facingDirection, MirrorType::Back);
        }
        else
        {
            renderer.renderLaserRemoved(itr->first);
            itr = lasers.erase(itr);
        }
    }
}

bool GameEventHandler::updatePlayersAtLaserPosition(ID laserID)
{
    bool playerHit = false;
    auto laserPosition = lasers.at(laserID).xy;
    
    for(int playerID = 0; playerID < players.size(); ++playerID)
    {
        auto player = players.at(playerID);
        
        if(player.xy == laserPosition)
        {
            auto laserShotByPlayerID = laserShotBy.at(laserID);
            auto& scoreOfPlayerThatShotLaser = playersScores.at(laserShotByPlayerID);
            
            if(laserShotByPlayerID == playerID)
            {
                --scoreOfPlayerThatShotLaser;
            }
            else
            {
                ++scoreOfPlayerThatShotLaser;
            }
            
            renderer.renderPlayerScore(laserShotByPlayerID, scoreOfPlayerThatShotLaser);
            renderer.renderPlayerShot(playerID);
            playerHit = true;
        }
    }

    return playerHit;
}

Direction GameEventHandler::reflectLaser(Direction prevDirection, MirrorType mirrorType)
{
    if(mirrorType == MirrorType::Forward)
    {
        switch (prevDirection)
        {
        case Direction::Right:
            return Direction::Up;
            break;
        case Direction::Up:
            return Direction::Right;
            break;
        case Direction::Down:
            return Direction::Left;
            break;
        case Direction::Left:
            return Direction::Down;
            break;
        }
    }
    else
    {
        switch(prevDirection)
        {
        case Direction::Right:
            return Direction::Down;
            break;
        case Direction::Down:
            return Direction::Right;
            break;
        case Direction::Left:
            return Direction::Up;
            break;
        case Direction::Up:
            return Direction::Left;
            break;
        }
        
    }
}

std::vector<ID> GameEventHandler::getWinners()
{
    int currHighestScore = -10000;
    std::vector<ID> winningPlayers;
    for(const auto& [playerID, score]: playersScores)
    {
        if(score > currHighestScore)
        {
            winningPlayers.clear();
            winningPlayers.push_back(playerID);
            currHighestScore = score;
        }
        else if(score == currHighestScore)
        {
            winningPlayers.push_back(playerID);
        }
    }
    std::sort(winningPlayers.begin(), winningPlayers.end());
    return winningPlayers;
}
