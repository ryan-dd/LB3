#include "GameStartParameters.h"
#include "PlayerInputInfo.h"
#include "Logger.h"

#include <stdexcept>
#include <sstream>

GameStartParameters::GameStartParameters(
    const std::unordered_map<ID, PlayerInputInfo> playersToBeControlled,
    const std::vector<Agent> players,
    const Arena arena,
    const std::chrono::seconds gameDuration):
        playersToBeControlled(playersToBeControlled),
        players(players),
        arena(arena),
        gameDuration(gameDuration)
{
    checkGameDurationValid();
    checkPlayersValid();
    checkControllingPlayerIDsValid();
}

void GameStartParameters::checkGameDurationValid()
{
    if(gameDuration.count() < 1)
    {
        throw std::invalid_argument("GameStartParameters::checkGameDurationValid - Seconds to play must be at least 1");
    }
}

void GameStartParameters::checkPlayersValid()
{
    if(players.size() < 2)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkPlayersValid - at least two players must be in the game, but only " << players.size() << " added";
        throw std::invalid_argument(errorMessage.str());
    }
    if(players.size() > 8)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkPlayersValid - Only up to 8 players are currently supported. ";
        errorMessage << "There were " << players.size() << " added";
        throw std::invalid_argument(errorMessage.str());
    }
    else if(players.size() < playersToBeControlled.size())
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkPlayersValid - number of players was less than playerIDs to be controlled. ";
        errorMessage << "Number of players: " << players.size();
        errorMessage << " Number of players to be controlled: " << playersToBeControlled.size();
        throw std::invalid_argument(errorMessage.str());
    }

    for(const auto& agent: players)
    {
        ObstacleType obstacleType;
        
        try
        {
            obstacleType = arena.at(agent.xy);
        }
        catch(const std::exception& e)
        {
            throw std::invalid_argument("GameStartParameters::GameStartParameters - Cannot place agent starting position out of arena");
        }

        if(obstacleType == ObstacleType::WALL)
        {
            throw std::invalid_argument("GameStartParameters::GameStartParameters - Cannot place agent starting position at wall");
        }
    }
}

void GameStartParameters::checkControllingPlayerIDsValid()
{
    if(playersToBeControlled.size() == 0)
    {
        throw std::invalid_argument("GameStartParameters::checkControllingPlayerIDsValid - No players specified to be controlled");
    }
    else if(playersToBeControlled.size() > players.size())
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkPlayersValid - playerIDs to be controlled was greater than number of players. ";
        errorMessage << "Number of players: " << players.size();
        errorMessage << " Number of players to be controlled: " << playersToBeControlled.size();
        throw std::invalid_argument(errorMessage.str());
    }

    for(const auto& [playerID, inputs]: playersToBeControlled)
    {
        if(playerID >= players.size())
        {
            std::stringstream errorMessage;
            errorMessage << "GameStartParameters::checkControllingPlayerIDsValid - requested controlled playerID was outside of valid playerIDs. ";
            errorMessage << "PlayerID: ";
            errorMessage << playerID;
            errorMessage << " Number of players: ";
            errorMessage << players.size();
        }
    }
}

int GameStartParameters::getNumberOfPlayers() const
{
    return players.size();
}