#include "GameRenderer.h"
#include "Color.h"
#include "Logger.h"

#include <string>
#include <sstream>

GameRenderer::GameRenderer(WINDOW* window, int numberPlayers): 
    window(window)
{
    initializeData(numberPlayers);
}

void GameRenderer::initializeData(int numberOfPlayers)
{
    int y, x;
    getmaxyx(window, y, x);
    int xIncrement = (x-5)/(numberOfPlayers-1);
    for (int i = 0; i < numberOfPlayers; i++)
    {
        char playerSymbol = std::to_string(i + 1).at(0);
        playerSymbols.insert({i, playerSymbol});
        playerColor.insert({i, LB3::Color::PLAYER_DEFAULT});
        playerScorePositions.insert({i, Vector2d(i*xIncrement, y-1)});
    }   
}

void GameRenderer::renderPlayerAppeared(ID playerID, Vector2d newPosition)
{
    playerPositions.insert({playerID, newPosition});
    renderPlayer(playerID);
}

void GameRenderer::renderPlayerMoved(ID playerID, Vector2d newPosition)
{
    auto& currPosition = playerPositions.at(playerID);
    playerColor.at(playerID) = LB3::Color::PLAYER_DEFAULT;
    renderArenaLocation(currPosition);
    currPosition = newPosition;
    renderAllPlayers();
}

void GameRenderer::renderPlayerShot(ID playerID)
{   
    playerColor.at(playerID) = LB3::Color::PLAYER_SHOT;
    renderPlayer(playerID);
}

void GameRenderer::renderPlayerTeleported(ID playerID, Vector2d newPosition)
{   
    auto& currPosition = playerPositions.at(playerID);
    renderArenaLocation(currPosition);
    currPosition = newPosition;
    playerColor.at(playerID) = LB3::Color::PLAYER_TELEPORTED;
    renderPlayer(playerID);
}

void GameRenderer::renderLaserAppeared(
    ID laserID, 
    Vector2d newPosition, 
    LaserOrientation orientation)
{
    lasers.emplace(laserID, newPosition);
    
    if(getArenaSymbol(newPosition) == ' ')
    {
        renderChar(newPosition, laserOrientationSymbol.at(orientation));
    }
}

void GameRenderer::renderLaserMoved(ID laserID, Vector2d newPosition, LaserOrientation orientation)
{
    auto& currPosition = lasers.at(laserID);
    renderArenaLocation(currPosition);
    
    if(getArenaSymbol(newPosition) == ' ')
    {
        renderChar(newPosition, laserOrientationSymbol.at(orientation));
    }

    currPosition = newPosition;
    renderAllPlayers();
}

void GameRenderer::renderLaserRemoved(ID laserID)
{
    const auto& laserPosition = lasers.at(laserID);
    renderArenaLocation(laserPosition);
    lasers.erase(laserID);
    renderAllPlayers();
}

void GameRenderer::renderPlayer(ID playerID)
{
    wattron(window, COLOR_PAIR(toInt(playerColor.at(playerID))));
    renderChar(playerPositions.at(playerID), playerSymbols.at(playerID));
    wattroff(window, COLOR_PAIR(toInt(playerColor.at(playerID))));
}

void GameRenderer::renderAllPlayers()
{
    for(auto iter = playerPositions.begin(); iter != playerPositions.end(); ++iter)
    {
        renderPlayer(iter->first);
    }
}

void GameRenderer::renderPlayerScore(ID playerID, int score)
{
    const auto& scorePosition = playerScorePositions.at(playerID);
    mvwprintw(window, scorePosition.y, scorePosition.x, clearString.c_str());
    std::stringstream displayString;
    displayString << playerID+1 << ":" << score;
    wattron(window, COLOR_PAIR(toInt(LB3::Color::DISPLAY_DEFAULT)));
    mvwprintw(window, scorePosition.y, scorePosition.x, displayString.str().c_str());
    wattroff(window, COLOR_PAIR(toInt(LB3::Color::DISPLAY_DEFAULT)));
}

void GameRenderer::renderArenaLocation(Vector2d location)
{
    renderChar(location, arenaSymbols.at(location.y).at(location.x));
}

void GameRenderer::renderSecondsLeft(int seconds)
{
    int y, x;
    getmaxyx(window, y, x);
    int printY = 0;
    int printX = x/2;
    auto secondsLeftStr = std::to_string(seconds);
    wattron(window, COLOR_PAIR(toInt(LB3::Color::DISPLAY_DEFAULT)));
    mvwprintw(window, printY, printX, clearString.c_str());
    mvwprintw(window, printY, printX, secondsLeftStr.c_str());
    wattroff(window, COLOR_PAIR(toInt(LB3::Color::DISPLAY_DEFAULT)));
}

void GameRenderer::renderArena(const Arena& arena)
{
    char obstacleSymbol = 'o';
    char forwardMirrorSymbol = '/';
    char backMirrorSymbol = '\\';
    char teleporterSymbol = '*';

    // Cache arena symbols
    arenaSymbols.resize(arena.getMaxY());
    for(auto& arenaSymbolRow: arenaSymbols)
    {
        arenaSymbolRow = std::vector<char>(arena.getMaxX(), ' ');
    }

    for (int y_index = 0; y_index < arena.getMaxY(); y_index++)
    {
        for (int x_index = 0; x_index < arena.getMaxX(); x_index++)
        {
            switch (arena.at(x_index, y_index))
            {
            case ObstacleType::OBSTACLE:
                renderChar(x_index, y_index, obstacleSymbol);
                arenaSymbols.at(y_index).at(x_index) = obstacleSymbol;
                break;
            case ObstacleType::FORWARD_MIRROR:
                renderChar(x_index, y_index, forwardMirrorSymbol);
                arenaSymbols.at(y_index).at(x_index) = forwardMirrorSymbol;
                break;
            case ObstacleType::BACK_MIRROR:
                renderChar(x_index, y_index, backMirrorSymbol);
                arenaSymbols.at(y_index).at(x_index) = backMirrorSymbol;
                break;
            case ObstacleType::TELEPORTER:
                renderChar(x_index, y_index, teleporterSymbol);
                arenaSymbols.at(y_index).at(x_index) = teleporterSymbol;
                break;
            default:
                break;
            }
        }
    }
}

char GameRenderer::getArenaSymbol(Vector2d input)
{
    return arenaSymbols.at(input.y).at(input.x);
}

void GameRenderer::renderChar(Vector2d location, char symbol)
{
    renderChar(location.x, location.y, symbol);
}

void GameRenderer::renderChar(int x, int y, char symbol)
{
    mvwaddch(window, y, x, symbol);
}
