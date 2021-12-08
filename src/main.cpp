#include "Mirror.h"
#include "Direction.h"
#include <iostream>
#include <ncurses.h>
#include "GameSession.h"

int main()
{
    GameSession session(20, 100);
    session.printToSession("Hello World: ");
    session.printToSession(" Welcome to The Game");
    session.waitForUserInput();
}