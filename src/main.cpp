#include <iostream>
#include <ncurses.h>
#include "GameSession.h"
#include <thread>

int main()
{
    int height = 20;
    int width = 70;
    GameSession session(width, height);
    session.printToSession("Welcome to The Game (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("Use the arrow keys to move, and \"q\" to quit. Hope you enjoy! ");
    session.waitForUserInput();
    session.clear();
    
    session.start();

    session.clear();
    session.printToSession("Thanks for playing!");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    session.waitForUserInput();
}