#include "GameSession.h"
#include "GameStartParameters.h"
#include "Logger.h"

#include <ncurses.h>

#include <thread>
#include <iostream>
#include <optional>

int main()
{
    Logger::initialize();
    
    int gameHeight = 20;
    int gameWidth = 70;

    Arena arena(gameWidth, gameHeight);
    arena.generateObstacles(ObstacleType::FORWARD_MIRROR, 40);
    arena.generateObstacles(ObstacleType::BACK_MIRROR, 40);
    arena.generateObstacles(ObstacleType::TELEPORTER, 40);
    
    std::vector<Agent> agents;
    agents.emplace_back(1, 1, Direction::RIGHT);
    agents.emplace_back(arena.getMaxX() - 2, arena.getMaxY() - 2, Direction::LEFT);
    agents.emplace_back(10, 10, Direction::LEFT);
    std::unordered_set<ID> playerIDsToBeControlled{0, 1};

    std::optional<GameStartParameters> parameters;
    
    try
    {
        parameters.emplace(
            playerIDsToBeControlled,
            agents,
            arena);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error occurred while initializing: " << '\n' << e.what() << '\n';
        Logger::log(e.what());
        return 0;
    }
    
    GameSession session(*parameters);
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