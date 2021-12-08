
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <ncurses.h>
#include <string>
#include "Player.h"

class GameSession
{
private:
    WINDOW* mWindow;
    Player player;
public:
    GameSession(int height, int width);
    ~GameSession();
    void waitForUserInput();
    void printToSession(const std::string& input);
    void clear();
    void controlPlayer();
};



#endif