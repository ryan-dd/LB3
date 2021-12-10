
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "GameRenderer.h"
#include "GameEventHandler.h"
#include "Agent.h"
#include "Direction.h"

class GameSession
{
private:
    WINDOW* mWindow;
    std::unique_ptr<GameRenderer> renderer;
    std::unique_ptr<GameEventHandler> eventHandler;

    struct PlayerInputInfo
    {
        int id = 0;
        char up = (char)KEY_UP;
        char down = (char)KEY_DOWN;
        char left = (char)KEY_LEFT;
        char right = (char)KEY_RIGHT;
        char laser = ' ';
    };

    PlayerInputInfo playerOneInfo;
    PlayerInputInfo playerTwoInfo;
    void initPlayerInputInfo();


    void updatePlayer(char input, PlayerInputInfo playerInfo);

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