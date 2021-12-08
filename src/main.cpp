#include "Mirror.h"
#include "Direction.h"
#include <iostream>
#include <ncurses.h>
#include "GameSession.h"

int main()
{
    GameSession session(20, 100);
    session.printToSession("Welcome to The Game (Press any key to continue)");
    session.waitForUserInput();
    session.printToSession("Use the arrow keys to move, and \"q\" to quit. Hope you enjoy! ");
    session.waitForUserInput();
    session.clear();
    session.start();
    // Control-c to exit
}