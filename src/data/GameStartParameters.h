#ifndef GAMESTARTPARAMETERS_H
#define GAMESTARTPARAMETERS_H

#include <vector>
#include <unordered_set>
#include <chrono>
#include "Agent.h"
#include "Arena.h"
#include "ID.h"
#include "PlayerInputInfo.h"

namespace LB3
{
struct GameStartParameters
{
    GameStartParameters(const std::unordered_map<ID, PlayerInputInfo> playersToBeControlled,
                        const std::vector<Agent> players,
                        const Arena arena,
                        std::chrono::seconds gameDuration = std::chrono::seconds(60));                 
    
    // IDs and controls of Players that will be controlled by this client
    const std::unordered_map<ID, PlayerInputInfo> playersToBeControlled;
    // Starting data for players. The playerIDs are based on indices of this data
    const std::vector<Agent> players;
    // The arena the game will be played on
    const Arena arena;
    // Seconds to play the game
    const std::chrono::seconds gameDuration;

    int getNumberOfPlayers() const;

    private:
        void checkControllingPlayerIDsValid();
        void checkPlayersValid();
        void checkGameDurationValid();
        // Arena handles its own validation
};
}

#endif // GAMESTARTPARAMETERS_H
