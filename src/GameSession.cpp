#include "GameSession.h"
#include "GameStartParameters.h"
#include "Color.h"

#include <thread>
#include <string>

GameSession::GameSession(const GameStartParameters parameters):
    gameDuration(parameters.gameDuration)
{
    int xMax = parameters.arena.getMaxX();
    int yMax = parameters.arena.getMaxY();
    initializeCurses(xMax, yMax);

    for(const auto [playerID, inputControls]: parameters.playersToBeControlled)
    {
        inputInfos.insert({playerID, inputControls});
    }
    
    int numPlayers = parameters.getNumberOfPlayers();
    renderer = std::make_unique<GameRenderer>(window, numPlayers);
    eventHandler = std::make_unique<GameEventHandler>(*renderer, parameters);
}

GameSession::~GameSession()
{
    cleanUpCurses();
}

void GameSession::start()
{   
    nodelay(window, true);
    eventHandler->start();

    auto now = std::chrono::steady_clock::now();
    auto nextTick = now + tickLength;
    
    auto start = now;
    auto nextSecond = now + std::chrono::seconds(1);
    int secondsLeftToPlay = gameDuration.count();
    while(now < start + gameDuration)
    {
        if(now > nextTick)
        {   
            updateState();
            nextTick += tickLength;
        }

        if(now > nextSecond)
        {
            nextSecond += std::chrono::seconds(1);
            --secondsLeftToPlay;
            renderer->renderSecondsLeft(secondsLeftToPlay);
        }

        char choice = wgetch(window);
        for (size_t playerID = 0; playerID < inputInfos.size(); playerID++)
        {
            updatePlayer(choice, playerID, inputInfos.at(playerID));
        }
        
        if(choice == 'q')
        {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        now = std::chrono::steady_clock::now();
    }

    nodelay(window, false);
    displayResults();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    waitForUserInput();
}

void GameSession::displayResults()
{
    this->clear();
    auto winnerIDs = eventHandler->getWinners();
    if(winnerIDs.size() == 1)
    {
        printToSession("Player " + std::to_string(winnerIDs.at(0) + 1) + " wins!");
        return;
    }

    queueToPrintToSession("Winners:");
    for(auto winnerID: winnerIDs)
    {
        queueToPrintToSession("Player " + std::to_string(winnerID+1));
    }
    printQueuedMessages();
}

void GameSession::updateState()
{
    eventHandler->step();
}

void GameSession::updatePlayer(char input, int id, PlayerInputInfo playerInfo)
{
    if(input == playerInfo.up)
    {
        eventHandler->movePlayer(id, Direction::Up);
    } 
    else if(input == playerInfo.down)
    {
        eventHandler->movePlayer(id, Direction::Down);
    }
    else if(input == playerInfo.left)
    {
        eventHandler->movePlayer(id, Direction::Left);
    }
    else if(input == playerInfo.right)
    {
        eventHandler->movePlayer(id, Direction::Right);
    }
    else if(input == playerInfo.laser)
    {
        eventHandler->newLaser(id);
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

void GameSession::queueToPrintToSession(const std::string& input)
{
    toPrint.push_back(input);
}

void GameSession::printQueuedMessages()
{
    werase(window);
    wrefresh(window);
    box(window, 0, 0);
    int yMax;
    int xMax;
    getmaxyx(window, yMax, xMax);
    int startY = yMax/2 - toPrint.size()/2;

    for(const auto& message: toPrint)
    {
        mvwprintw(window, startY, xMax/2 - message.size()/2, message.c_str());
        ++startY;
    }

    wrefresh(window);
    toPrint.clear();
}

void GameSession::clear()
{
    werase(window);
    wrefresh(window);
    box(window, 0, 0);
    wrefresh(window);
}

void GameSession::initializeCurses(int xMax, int yMax)
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
        std::this_thread::sleep_for(std::chrono::seconds(1));
        endwin();
        exit(1);
    }

    start_color();
	init_pair(toInt(LB3::Color::ArenaDefault), COLOR_WHITE, COLOR_BLACK); // Default color for game
	init_pair(toInt(LB3::Color::PlayerDefault), COLOR_YELLOW, COLOR_BLACK); // Default player color 
    init_pair(toInt(LB3::Color::PlayerShot), COLOR_RED, COLOR_BLACK); // Player hit by laser color
    init_pair(toInt(LB3::Color::PlayerTeleported), COLOR_MAGENTA, COLOR_BLACK); // Player teleport color
    init_pair(toInt(LB3::Color::DisplayDefault), COLOR_GREEN, COLOR_BLACK); // Score and timer color
	
    attron(COLOR_PAIR(toInt(LB3::Color::ArenaDefault)));
	
    refresh();
    box(window, 0, 0);
}

void GameSession::cleanUpCurses()
{
    endwin();
}
