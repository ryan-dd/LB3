
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <ncurses.h>
#include <string>
#include "Agent.h"
class GameSession
{
private:
    WINDOW* mWindow;
    Agent player;
    Agent player2;
    Agent lazer;
public:
    GameSession(int height, int width);
    ~GameSession();
    void waitForUserInput();
    void printToSession(const std::string& input);
    void clear();
    void start();
    
    void updateState();
    void redraw();
};



#endif