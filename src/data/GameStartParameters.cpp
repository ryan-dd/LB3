#include "GameStartParameters.h"
#include <stdexcept>
#include <Logger.h>
#include <sstream>

GameStartParameters::GameStartParameters(
    const std::unordered_set<ID> playerIDsToBeControlled,
    const std::vector<Agent> agents,
    const Arena arena,
    const std::chrono::seconds gameDuration):
        playerIDsToBeControlled(playerIDsToBeControlled),
        agents(agents),
        arena(arena),
        gameDuration(gameDuration)
{
    checkGameDurationValid();
    checkAgentsValid();
    checkControllingPlayerIDsValid();
}

void GameStartParameters::checkGameDurationValid()
{
    if(gameDuration.count() < 1)
    {
        throw std::invalid_argument("GameStartParameters::checkGameDurationValid - Seconds to play must be at least 1");
    }
}

void GameStartParameters::checkAgentsValid()
{
    if(agents.size() < 2)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkAgentsValid - at least two agents must be in the game, but only " << agents.size() << " added";
        throw std::invalid_argument(errorMessage.str());
    }
    if(agents.size() > 8)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkAgentsValid - Only up to 8 players are currently supported. ";
        errorMessage << "There were " << agents.size() << " added";
        throw std::invalid_argument(errorMessage.str());
    }
    else if(agents.size() < playerIDsToBeControlled.size())
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkAgentsValid - number of agents was less than playerIDs to be controlled. ";
        errorMessage << "Number of player starting positions: " << agents.size();
        errorMessage << " Number of players to be controlled: " << playerIDsToBeControlled.size();
        throw std::invalid_argument(errorMessage.str());
    }

    for(const auto& agent: agents)
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
    if(playerIDsToBeControlled.size() == 0)
    {
        throw std::invalid_argument("GameStartParameters::checkControllingPlayerIDsValid - No agents specified to be controlled");
    }
    else if(playerIDsToBeControlled.size() > 2)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::checkControllingPlayerIDsValid - This game currently supports controlling only up to two players, but ";
        errorMessage << playerIDsToBeControlled.size() << " players were requested";
        throw std::invalid_argument(errorMessage.str());
    }

    for(const auto& playerID: playerIDsToBeControlled)
    {
        if(playerID >= agents.size())
        {
            std::stringstream errorMessage;
            errorMessage << "GameStartParameters::checkControllingPlayerIDsValid - requested controlled playerID was outside of valid playerIDs. ";
            errorMessage << "PlayerID: ";
            errorMessage << playerID;
            errorMessage << " Number of player starting positions: ";
            errorMessage << agents.size();
        }
    }
}

int GameStartParameters::getNumberOfPlayers() const
{
    return agents.size();
}