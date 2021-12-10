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
    playerTwoInfo.laser = 'z';
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

    auto start = std::chrono::steady_clock::now();
    auto tick = std::chrono::milliseconds(50);
    auto nextTick = start + tick;
    nodelay(mWindow, true);
    
    auto now = start;
    int secondsToPlay = 60;
    int secondsLeftToPlay = secondsToPlay;
    auto nextSecond = now + std::chrono::seconds(1);

    while(now < start + std::chrono::seconds(secondsToPlay))
    {
        if(now > nextTick)
        {   
            updateState();
            nextTick += tick;
        }

        if(now > nextSecond)
        {
            nextSecond += std::chrono::seconds(1);
            --secondsLeftToPlay;
            renderer->renderSecondsLeft(secondsLeftToPlay);
        }

        char choice = wgetch(mWindow);
        updatePlayer(choice, playerOneInfo);
        updatePlayer(choice, playerTwoInfo);
        
        if(choice == 'q')
        {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        now = std::chrono::steady_clock::now();
    }

    nodelay(mWindow, false);
    
    this->clear();
    auto [p1score, p2score] = eventHandler->getFinalScores();
    if(p1score > p2score)
    {
        printToSession("Player 1 wins!");
    }
    else if(p2score > p1score)
    {
        printToSession("Player 2 wins!");
    }
    else
    {
        printToSession("Tie!");
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    waitForUserInput();
}



void GameSession::updateState()
{
    eventHandler->step();
}
