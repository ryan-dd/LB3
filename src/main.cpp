#include <iostream>
#include <ncurses.h>
#include "GameSession.h"

int main()
{
    int height = 20;
    int width = 100;
    GameSession session(width, height);
    session.printToSession("Welcome to The Game (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("Use the arrow keys to move, and \"q\" to quit. Hope you enjoy! ");
    session.waitForUserInput();
    session.clear();
    session.start();
}