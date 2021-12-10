#include "GameRenderer.h"

#include <string>
#include "Logger.h"

GameRenderer::GameRenderer(WINDOW* window): 
    window(window)
{
    playerSymbols.insert({0, '@'});
    playerSymbols.insert({1, '&'});

    int y, x;
    getmaxyx(window, y, x);
    playerScorePositions.insert({1, Vector2d(0, y-1)});
    playerScorePositions.insert({0, Vector2d(x-2, y-1)});
}

void GameRenderer::renderPlayerFirstTime(ID playerID, Vector2d newPosition)
{
    playerPositions.insert({playerID, newPosition});
    renderChar(newPosition, playerSymbols.at(playerID));
}

void GameRenderer::renderPlayer(ID playerID, Vector2d newPosition)
{
    auto& currPosition = playerPositions.at(playerID);
    reRerenderArenaLocation(currPosition);
    currPosition = newPosition;
    reRenderAllPlayers();
}

void GameRenderer::reRenderPlayer(ID playerID)
{
    renderChar(playerPositions.at(playerID), playerSymbols.at(playerID));
}

void GameRenderer::reRenderAllPlayers()
{
    for(auto iter = playerPositions.begin(); iter != playerPositions.end(); ++iter)
    {
        reRenderPlayer(iter->first);
    }
}

void GameRenderer::reRerenderArenaLocation(Vector2d location)
{
    renderChar(location, arenaSymbols.at(location.y).at(location.x));
}

void GameRenderer::renderSecondsLeft(int seconds)
{
    int y, x;
    getmaxyx(window, y, x);
    std::string clearString = "  ";
    int printY = y-1;
    int printX = x/2;
    auto secondsLeftStr = std::to_string(seconds);
    mvwprintw(window, printY, printX, clearString.c_str());
    mvwprintw(window, printY, printX, secondsLeftStr.c_str());
}

void GameRenderer::renderArena(const Arena& arena)
{
    char obstacleSymbol = 'o';
    char forwardMirrorSymbol = '/';
    char backMirrorSymbol = '\\';

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
            default:
                break;
            }
        }
    }
}

void GameRenderer::renderPlayerScore(ID playerID, int score)
{
    const auto& scorePosition = playerScorePositions.at(playerID);
    auto scoreString = std::to_string(score);
    mvwprintw(window, scorePosition.y, scorePosition.x, scoreString.c_str());
}

void GameRenderer::renderLaserFirstTime(
    ID laserID, 
    Vector2d newPosition, 
    LaserOrientation orientation)
{
    lasers.emplace(laserID, newPosition);
    
    if(getArenaSymbol(newPosition) != ' ')
    {
        renderChar(newPosition, laserOrientationSymbol.at(orientation));
    }
}

void GameRenderer::renderLaser(ID laserID, Vector2d newPosition, LaserOrientation orientation)
{
    auto& currPosition = lasers.at(laserID);
    reRerenderArenaLocation(currPosition);
    renderChar(newPosition, laserOrientationSymbol.at(orientation));
    currPosition = newPosition;
    reRenderAllPlayers();
}

void GameRenderer::removeLaser(ID laserID)
{
    const auto& laserPosition = lasers.at(laserID);
    reRerenderArenaLocation(laserPosition);
    lasers.erase(laserID);
    reRenderAllPlayers();
}

char GameRenderer::getArenaSymbol(Vector2d input)
{
    return arenaSymbols.at(input.y).at(input.x);
}
