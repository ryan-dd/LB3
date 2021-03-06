
#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "GameRenderer.h"
#include "GameEventHandler.h"
#include "GameStartParameters.h"
#include "PlayerInputInfo.h"

#include <ncurses.h>
#include <string>
#include <memory>
#include <chrono>

namespace LB3
{
class GameSession
{
private:
    WINDOW* window;
    std::unique_ptr<GameRenderer> renderer;
    std::unique_ptr<GameEventHandler> eventHandler;
    std::unordered_map<ID, PlayerInputInfo> inputInfos;

    const std::chrono::seconds gameDuration;
    const std::chrono::milliseconds tickLength = std::chrono::milliseconds(50);
    void updatePlayer(char input, int id, PlayerInputInfo playerInfo);

    std::vector<std::string> toPrint;
    void initializeCurses(int xMax, int yMax);
    void cleanUpCurses();
    void displayResults();
    void queueToPrintToSession(const std::string& input);
    void printQueuedMessages();
public:
    GameSession(const GameStartParameters parameters);
    ~GameSession();
    void printInstructions();
    void printOpeningSequence();
    void printToSession(const std::string& input);
    void waitForUserInput();
    void clear();

    void start();
    void updateState();
};
}

#endif