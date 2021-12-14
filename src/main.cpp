#include "GameSession.h"
#include "GameStartParameters.h"
#include "Logger.h"
#include "PlayerInputInfo.h"

#include <ncurses.h>

#include <thread>
#include <iostream>
#include <optional>

int main()
{
    LB3::Logger::initialize();
    
    int gameHeight = 25;
    int gameWidth = 60;

    LB3::Arena arena(gameWidth, gameHeight);
    arena.generateObstacles(LB3::ObstacleType::ForwardMirror, 40);
    arena.generateObstacles(LB3::ObstacleType::BackMirror, 40);
    arena.generateObstacles(LB3::ObstacleType::Teleporter, 40);

    std::vector<LB3::Agent> players;
    players.emplace_back(1, 1, LB3::Direction::Right);
    players.emplace_back(arena.getMaxX() - 2, arena.getMaxY() - 2, LB3::Direction::Left);
    players.emplace_back(20, 20, LB3::Direction::Left);
    
    std::unordered_map<LB3::ID, LB3::PlayerInputInfo> playersToBeControlled{
        {0, LB3::getPlayerOneInputInfo()},
        {1, LB3::getPlayerTwoInputInfo()},
        {2, LB3::getPlayerThreeInputInfo()}};

    std::optional<LB3::GameStartParameters> parameters;
    
    try
    {
        parameters.emplace(
            playersToBeControlled,
            players,
            arena);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error occurred while initializing: " << '\n' << e.what() << '\n';
        LB3::Logger::log(e.what());
        return 0;
    }
    
    LB3::GameSession session(*parameters);
    session.printToSession("Welcome to Light Battle 3000!!! (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("Shoot your opponent(s) to increase your score!");
    session.waitForUserInput();

    session.queueToPrintToSession("P1 - Arrow keys to move, space bar to shoot");
    session.queueToPrintToSession("");
    session.queueToPrintToSession("P2 - w a s d to move, v to shoot.");
    session.queueToPrintToSession("");
    session.queueToPrintToSession("\'/\' and \'\\\' are mirrors, and \'*\' are teleporters");
    session.queueToPrintToSession("");
    session.queueToPrintToSession("Press \"q\" to quit. Hope you enjoy! ");
    session.printQueuedMessages();
    session.waitForUserInput();
    session.clear();
    
    session.start();

    session.clear();
    session.printToSession("Thanks for playing!");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    session.waitForUserInput();
}