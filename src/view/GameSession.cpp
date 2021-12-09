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
    getmaxyx(mWindow, maxY, maxX);
    player1 = Agent(maxX, maxY, maxX-2, maxY-2);
    player2 = Agent(maxX, maxY, 1, 1);
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
    playerTwoInfo.laser = 'g';
    playerTwoInfo.representation = '&';
}

void GameSession::updatePlayer(char input, Agent& player, PlayerInfo playerInfo)
{
    auto [x, y] = player.getXY();
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
    else if(input == playerInfo.laser)
    {
        auto startPoint = player.getXY() + toVector(player.getLastDirection());
        
        // Check if a valid position to construct
        if(startPoint.first > 1 && startPoint.first < maxX-1 &&
           startPoint.second > 1 && startPoint.second < maxY-1)
        {
            lasers.push_back(Agent(maxX, maxY, startPoint.first, startPoint.second, player.getLastDirection()));
        }
    }
    
    auto [xAfter, yAfter] = player.getXY();
    mvwaddch(mWindow, yAfter, xAfter, playerInfo.representation);
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
    auto [x1, y1] = player1.getXY();
    mvwaddch(mWindow, y1, x1, playerOneInfo.representation);

    auto [x2, y2] = player2.getXY();
    mvwaddch(mWindow, y2, x2, playerTwoInfo.representation);
    
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
        updatePlayer(choice, player1, playerOneInfo);
        updatePlayer(choice, player2, playerTwoInfo);
        if(choice == 'q')
        {
            return;
        }
    }
}

void GameSession::updateState()
{
    // Update non-player environment
    for(auto& laser: lasers)
    {
        if(laser.getXY() != player1.getXY() && laser.getXY() != player2.getXY())
        {
            auto [x, y] = laser.getXY();
            mvwaddch(mWindow, y, x, ' ');
        }

        switch (laser.getLastDirection())
        {
        case Direction::UP:
            laser.requestUp();
            break;
        case Direction::DOWN:
            laser.requestDown();
            break;
        case Direction::LEFT:
            laser.requestLeft();
            break;
        case Direction::RIGHT:
            laser.requestRight();
            break;
        default:
            break;
        }

        if(!laser.justMovedAgainstObstacle())
        {
            auto [x, y] = laser.getXY();
            mvwaddch(mWindow, y, x, laserDirectionToChar[laser.getLastDirection()]);
        }
    }

    std::erase_if(lasers, [](const Agent& laser){return laser.justMovedAgainstObstacle();});
}
