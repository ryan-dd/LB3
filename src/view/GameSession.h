
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <ncurses.h>
#include <string>
#include "Agent.h"
class GameSession
{
private:
    WINDOW* mWindow;
    Agent player1;
    Agent player2;
    Agent lazer;

    struct PlayerInfo
    {
        char up = (char)KEY_UP;
        char down = (char)KEY_DOWN;
        char left = (char)KEY_LEFT;
        char right = (char)KEY_RIGHT;
        char representation = '@';
    };

    PlayerInfo playerOneInfo;
    PlayerInfo playerTwoInfo;

    void initPlayerInfo();
    void updatePlayer(char input, Agent& player, PlayerInfo playerInfo);

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