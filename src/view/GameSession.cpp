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
    player = Agent(maxX, maxY, 2, 2);
    player2 = Agent(maxX, maxY, maxX-2, maxY-2);
    lazer = Agent(maxX, maxY, 3, 3);
    lazer.requestRight();
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

void GameSession::start()
{   
    auto& xy = player.getXY();
    mvwaddch(mWindow, xy.second, xy.first, '@');

    auto& xy2 = player2.getXY();
    mvwaddch(mWindow, xy2.second, xy2.first, '&');
    
    auto& [x, y] = lazer.getXY();
    mvwaddch(mWindow, y, x, '-');

    auto tick = std::chrono::milliseconds(7);
    auto nextTick = std::chrono::steady_clock::now() + tick;
    timeout(1);
    nodelay(mWindow, true);

    while(true)
    {
        int choice = wgetch(mWindow);
        switch (choice)
        {
        case KEY_UP:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestUp();
            mvwaddch(mWindow, xy.second, xy.first, '@');
            break;
        case KEY_DOWN:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestDown();
            mvwaddch(mWindow, xy.second, xy.first, '@');
            break;
        case KEY_LEFT:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestLeft();
            mvwaddch(mWindow, xy.second, xy.first, '@');
            break;
        case KEY_RIGHT:
            mvwaddch(mWindow, xy.second, xy.first, ' ');
            player.requestRight();
            mvwaddch(mWindow, xy.second, xy.first, '@');
            break;
        case 'w':
            mvwaddch(mWindow, xy2.second, xy2.first, ' ');
            player2.requestUp();
            mvwaddch(mWindow, xy2.second, xy2.first, '&');
            break;
        case 's':
            mvwaddch(mWindow, xy2.second, xy2.first, ' ');
            player2.requestDown();
            mvwaddch(mWindow, xy2.second, xy2.first, '&');
            break;
        case 'a':
            mvwaddch(mWindow, xy2.second, xy2.first, ' ');
            player2.requestLeft();
            mvwaddch(mWindow, xy2.second, xy2.first, '&');
            break;
        case 'd':
            mvwaddch(mWindow, xy2.second, xy2.first, ' ');
            player2.requestRight();
            mvwaddch(mWindow, xy2.second, xy2.first, '&');
            break;
        
        case 'q':
            return;
        }

        if(std::chrono::steady_clock::now() > nextTick)
        {   
            updateState();
            nextTick += tick;
        }
    }
}

void GameSession::updateState()
{
    auto& [x, y] = lazer.getXY();
    mvwaddch(mWindow, y, x, ' ');
    lazer.requestRight();
    mvwaddch(mWindow, y, x, '-');
}
