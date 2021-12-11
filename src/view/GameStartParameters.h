#ifndef GAMESTARTPARAMETERS_H
#define GAMESTARTPARAMETERS_H

#include <vector>
#include <unordered_set>
#include <chrono>
#include "Agent.h"
#include "Arena.h"
#include "ID.h"

struct GameStartParameters
{
    GameStartParameters(const std::unordered_set<ID> playerIDsToBeControlled,
                        const std::vector<Agent> agents,
                        const Arena arena,
                        std::chrono::seconds gameDuration = std::chrono::seconds(60));                 
    
    // IDs of Players that will be controlled by this client
    const std::unordered_set<ID> playerIDsToBeControlled;
    // Starting positions of Players. The number of players and playerIDs (based on indices) are determined from this data
    const std::vector<Agent> agents;
    // The arena the game will be played on
    const Arena arena;
    // Seconds to play the game
    const std::chrono::seconds gameDuration;

    int getNumberOfPlayers() const;

    private:
        void checkControllingPlayerIDsValid();
        void checkAgentsValid();
        void checkGameDurationValid();
        // Arena handles its own validation
};

#endif // GAMESTARTPARAMETERS_H
