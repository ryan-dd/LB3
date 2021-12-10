#include "GameSession.h"
#include <thread>

GameSession::GameSession(int xMax, int yMax)
{
    initscr();
    mWindow = newwin(yMax, xMax, 0, 0);
    cbreak(); // Allow to control-c out of the game
    noecho(); // Don't print typed characters
    curs_set(0); // Hide cursor
    keypad(mWindow, true); // Can use keyboard characters
    refresh();
    box(mWindow, 0, 0);
    
    renderer = std::make_unique<GameRenderer>(mWindow);
    eventHandler = std::make_unique<GameEventHandler>(*renderer, xMax, yMax);
    initPlayerInputInfo();
}

GameSession::~GameSession()
{
    endwin();
}

void GameSession::initPlayerInputInfo()
{
    // Player 1 has default info
    playerTwoInfo.id = 1;
    playerTwoInfo.up = 'w';
    playerTwoInfo.down = 's';
    playerTwoInfo.left = 'a';
    playerTwoInfo.right = 'd';
    playerTwoInfo.laser = 'g';
}

void GameSession::updatePlayer(char input, PlayerInputInfo playerInfo)
{
    if(input == playerInfo.up)
    {
        eventHandler->movePlayer(playerInfo.id, Direction::UP);
    } 
    else if(input == playerInfo.down)
    {
        eventHandler->movePlayer(playerInfo.id, Direction::DOWN);
    }
    else if(input == playerInfo.left)
    {
        eventHandler->movePlayer(playerInfo.id, Direction::LEFT);
    }
    else if(input == playerInfo.right)
    {
        eventHandler->movePlayer(playerInfo.id, Direction::RIGHT);
    }
    else if(input == playerInfo.laser)
    {
        eventHandler->newLaser(playerInfo.id);
    }
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
    eventHandler->start();

    auto tick = std::chrono::milliseconds(50);
    auto nextTick = std::chrono::steady_clock::now() + tick;
    nodelay(mWindow, true);
    
    while(true)
    {
        if(std::chrono::steady_clock::now() > nextTick)
        {   
            updateState();
            nextTick += tick;
        }

        char choice = wgetch(mWindow);
        updatePlayer(choice, playerOneInfo);
        updatePlayer(choice, playerTwoInfo);
        
        if(choice == 'q')
        {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void GameSession::updateState()
{
    eventHandler->step();
}
