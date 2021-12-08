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
    player1 = Agent(maxX, maxY, 1, 1);
    player2 = Agent(maxX, maxY, maxX-2, maxY-2);
    initPlayerInfo();
}

GameSession::~GameSession()
{
    endwin();
}

void GameSession::initPlayerInfo()
{
    playerTwoInfo.up = 'w';
    playerTwoInfo.down = 's';
    playerTwoInfo.left = 'a';
    playerTwoInfo.right = 'd';
    playerTwoInfo.representation = '&';
}

void GameSession::updatePlayer(char input, Agent& player, PlayerInfo playerInfo)
{
    auto& [x, y] = player.getXY();
    mvwaddch(mWindow, y, x, ' ');

    if(input == playerInfo.up)
    {
        player.requestUp();
    } 
    else if(input == playerInfo.down)
    {
        player.requestDown();
    }
    else if(input == playerInfo.left)
    {
        player.requestLeft();
    }
    else if(input == playerInfo.right)
    {
        player.requestRight();
    }
    
    mvwaddch(mWindow, y, x, playerInfo.representation);
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
    auto& [x1, y1] = player1.getXY();
    mvwaddch(mWindow, y1, x1, playerOneInfo.representation);

    auto& [x2, y2] = player2.getXY();
    mvwaddch(mWindow, y2, x2, playerTwoInfo.representation);
    
    auto tick = std::chrono::milliseconds(7);
    auto nextTick = std::chrono::steady_clock::now() + tick;
    nodelay(mWindow, true);

    while(true)
    {
        char choice = wgetch(mWindow);
        updatePlayer(choice, player1, playerOneInfo);
        updatePlayer(choice, player2, playerTwoInfo);
        if(choice == 'q')
        {
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
    // Update non-player environment
}
