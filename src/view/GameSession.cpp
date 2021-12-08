#include "GameSession.h"

GameSession::GameSession(int height, int width)
{
    initscr();
    mWindow = newwin(height, width, 0, 0);
    cbreak(); // Allow to control-c out of the game
    noecho(); // Don't print typed characters
    refresh();
    box(mWindow, 0, 0);
}

GameSession::~GameSession()
{
    endwin();
}

void GameSession::waitForUserInput()
{
    getch();
}

void GameSession::printToSession(const std::string& input)
{
    int ynext;
    int xnext;
    getyx(mWindow, ynext, xnext);
    mvwprintw(mWindow, ++ynext, ++xnext, input.c_str());
    wrefresh(mWindow);
}


