#include <iostream>
#include <ncurses.h>
#include "GameSession.h"
#include <thread>
#include "Logger.h"

int main()
{
    Logger::initialize();
    int height = 20;
    int width = 70;
    GameSession session(width, height);
    session.printToSession("Welcome to Light Battle 3000!!! (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("P1 - Arrow keys to move, space bar to shoot");
    session.waitForUserInput();
    session.printToSession("P2 - w a s d to move, x to shoot.");
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