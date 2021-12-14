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
    Logger::initialize();
    
    int gameHeight = 25;
    int gameWidth = 60;

    Arena arena(gameWidth, gameHeight);
    arena.generateObstacles(ObstacleType::ForwardMirror, 40);
    arena.generateObstacles(ObstacleType::BackMirror, 40);
    arena.generateObstacles(ObstacleType::Teleporter, 40);

    std::vector<Agent> players;
    players.emplace_back(1, 1, Direction::Right);
    players.emplace_back(arena.getMaxX() - 2, arena.getMaxY() - 2, Direction::Left);
    players.emplace_back(20, 20, Direction::Left);
    
    std::unordered_map<ID, PlayerInputInfo> playersToBeControlled{
        {0, getPlayerOneInputInfo()},
        {1, getPlayerTwoInputInfo()},
        {2, getPlayerThreeInputInfo()}};

    std::optional<GameStartParameters> parameters;
    
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