#include <iostream>
#include <ncurses.h>
#include "GameSession.h"
#include "GameStartParameters.h"
#include <thread>
#include "Logger.h"

int main()
{
    Logger::initialize();
    
    int gameHeight = 20;
    int gameWidth = 70;

    Arena arena(gameWidth, gameHeight);
    arena.generateObstacles(ObstacleType::FORWARD_MIRROR, 40);
    arena.generateObstacles(ObstacleType::BACK_MIRROR, 40);
    arena.generateObstacles(ObstacleType::TELEPORTER, 40);
    Agent playerOne(1, 1, Direction::RIGHT);
    Agent playerTwo(arena.getMaxX() - 2, arena.getMaxY() - 2, Direction::LEFT);
    std::vector<Agent> agents{playerOne, playerTwo};
    std::unordered_set<ID> playerIDsToBeControlled{0, 1};

    GameStartParameters parameters(
        playerIDsToBeControlled,
        agents,
        arena
    );

    GameSession session(parameters);
    
    session.printToSession("Welcome to Light Battle 3000!!! (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("P1 - w a s d to move, v to shoot.");
    session.waitForUserInput();
    session.printToSession("P2 - Arrow keys to move, space bar to shoot");
    session.waitForUserInput();
    session.printToSession("Also, press \"q\" to quit. Hope you enjoy! ");
    session.waitForUserInput();
    session.clear();
    
    session.start();

    session.clear();
    session.printToSession("Thanks for playing!");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    session.waitForUserInput();
}