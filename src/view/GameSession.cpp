#include "GameSession.h"

GameSession::GameSession(int height, int width)
{
    initscr();
    mWindow = newwin(height, width, 0, 0);
    cbreak(); // Allow to control-c out of the game
    noecho(); // Don't print typed characters
    curs_set(0); // Hide cursor
    keypad(mWindow, true); // Can use keyboard characters
    refresh();
    box(mWindow, 0, 0);
    int maxY;
    int maxX;

    getmaxyx(mWindow, maxY, maxX);
    player = Player(maxX, maxY);
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
    werase(mWindow);
    wrefresh(mWindow);
    box(mWindow, 0, 0);
    int yMax;
    int xMax;
    getmaxyx(mWindow, yMax, xMax);
    mvwprintw(mWindow, yMax/2, xMax/2 - input.size()/2, input.c_str());
    wrefresh(mWindow);
}

void GameSession::clear()
{
    werase(mWindow);
    wrefresh(mWindow);
    box(mWindow, 0, 0);
    wrefresh(mWindow);
}

void GameSession::controlPlayer()
{   
    auto& xy = player.getXY();
    mvwaddch(mWindow, xy.second, xy.first, '@');

    while(true)
    {
        int choice = wgetch(mWindow);
        switch (choice)
        {
        case KEY_UP:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestUp();
            break;
        case KEY_DOWN:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestDown();
            break;
        case KEY_LEFT:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestLeft();
            break;
        case KEY_RIGHT:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestRight();
            break;
        case 'q':
            return;
        }

        mvwaddch(mWindow, xy.second, xy.first, '@');
    }

}


