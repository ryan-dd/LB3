
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <ncurses.h>
#include <string>

class GameSession
{
private:
    WINDOW* mWindow;
public:
    GameSession(int height, int width);
    ~GameSession();
    void waitForUserInput();
    void printToSession(const std::string& input);
};



#endif