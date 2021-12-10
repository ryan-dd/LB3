#include "GameSession.h"
#include <thread>

GameSession::GameSession(int xMax, int yMax)
{
    initscr();
    window = newwin(yMax, xMax, 0, 0);
    cbreak(); // Allow to control-c out of the game
    noecho(); // Don't print typed characters
    curs_set(0); // Hide cursor
    keypad(window, true); // Can use keyboard characters

    if(!has_colors())
    {
        printToSession("Your terminal doesn't support colors. Please switch to one that does");
        endwin();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        exit(1);
    }

    start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(0));
	
    refresh();
    box(window, 0, 0);
    
    renderer = std::make_unique<GameRenderer>(window);
    eventHandler = std::make_unique<GameEventHandler>(*renderer, xMax, yMax);
    initPlayerInputInfo();
}

GameSession::~GameSession()
{
    endwin();
}

void GameSession::initPlayerInputInfo()
{
    // Player 2 has default info
    playerTwoInfo.id = 1;

    playerOneInfo.id = 0;
    playerOneInfo.up = 'w';
    playerOneInfo.down = 's';
    playerOneInfo.left = 'a';
    playerOneInfo.right = 'd';
    playerOneInfo.laser = 'v';
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
    werase(window);
    wrefresh(window);
    box(window, 0, 0);
    int yMax;
    int xMax;
    getmaxyx(window, yMax, xMax);
    mvwprintw(window, yMax/2, xMax/2 - input.size()/2, input.c_str());
    wrefresh(window);
}

void GameSession::clear()
{
    werase(window);
    wrefresh(window);
    box(window, 0, 0);
    wrefresh(window);
}

void GameSession::start()
{   
    eventHandler->start();

    auto start = std::chrono::steady_clock::now();
    auto tick = std::chrono::milliseconds(50);
    auto nextTick = start + tick;
    
    auto now = start;
    int secondsToPlay = 60;
    int secondsLeftToPlay = secondsToPlay;
    auto nextSecond = now + std::chrono::seconds(1);
    nodelay(window, true);

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

        char choice = wgetch(window);
        updatePlayer(choice, playerOneInfo);
        updatePlayer(choice, playerTwoInfo);
        
        if(choice == 'q')
        {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        now = std::chrono::steady_clock::now();
    }

    nodelay(window, false);
    
    this->clear();
    auto scores = eventHandler->getFinalScores();
    auto p1score = scores.first;
    auto p2score = scores.second;
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
    std::this_thread::sleep_for(std::chrono::seconds(1));
    waitForUserInput();
}

void GameSession::updateState()
{
    eventHandler->step();
}
