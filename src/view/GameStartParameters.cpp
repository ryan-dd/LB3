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
    if(gameDuration.count() < 1)
    {
        throw std::invalid_argument("GameStartParameters::GameStartParameters - Seconds to play must be at least 1");
    }

    if(playerIDsToBeControlled.size() == 0)
    {
        throw std::invalid_argument("GameStartParameters::GameStartParameters - No Players specified to be controlled");
    }
    else if(playerIDsToBeControlled.size() > 2)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::GameStartParameters - This game currently supports controlling only up to two players, but ";
        errorMessage << playerIDsToBeControlled.size() << " were requested";
        throw std::invalid_argument(errorMessage.str());
    }

    if(agents.size() > 8)
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::GameStartParameters - Only up to 8 players are currently supported. ";
        errorMessage << "There were " << agents.size() << " requested";
        throw std::invalid_argument(errorMessage.str());
    }
    else if(agents.size() < playerIDsToBeControlled.size())
    {
        std::stringstream errorMessage;
        errorMessage << "GameStartParameters::GameStartParameters - agents size was less than playerIDs to be controlled. ";
        errorMessage << "Number of player starting positions: " << agents.size();
        errorMessage << " Number of players to be controlled: " << playerIDsToBeControlled.size();
        throw std::invalid_argument(errorMessage.str());
    }

    for(const auto& playerID: playerIDsToBeControlled)
    {
        if(playerID >= agents.size())
        {
            std::stringstream errorMessage;
            errorMessage << "GameStartParameters::GameStartParameters - requested controlled playerID was outside of valid playerIDs. ";
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