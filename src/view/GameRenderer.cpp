#include "GameRenderer.h"

#include <string>
#include "Logger.h"

GameRenderer::GameRenderer(WINDOW* window): 
    window(window)
{
    playerSymbols.insert({0, '1'});
    playerSymbols.insert({1, '2'});

    playerColor.insert({0, 1});
    playerColor.insert({1, 1});

    int y, x;
    getmaxyx(window, y, x);
    playerScorePositions.insert({0, Vector2d(0, y-1)});
    playerScorePositions.insert({1, Vector2d(x-2, y-1)});
}

void GameRenderer::renderPlayerAppeared(ID playerID, Vector2d newPosition)
{
    playerPositions.insert({playerID, newPosition});
    reRenderPlayer(playerID);
}

void GameRenderer::renderPlayerMoved(ID playerID, Vector2d newPosition)
{
    auto& currPosition = playerPositions.at(playerID);
    playerColor.at(playerID) = 1; // Move color
    reRerenderArenaLocation(currPosition);
    currPosition = newPosition;
    reRenderAllPlayers();
}

void GameRenderer::renderPlayerShot(ID playerID)
{   
    playerColor.at(playerID) = 2; // Shot color
    reRenderPlayer(playerID);
}

void GameRenderer::renderPlayerTeleported(ID playerID, Vector2d newPosition)
{   
    auto& currPosition = playerPositions.at(playerID);
    reRerenderArenaLocation(currPosition);
    currPosition = newPosition;
    playerColor.at(playerID) = 3; // Teleport color
    reRenderPlayer(playerID);
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
    reRerenderArenaLocation(currPosition);
    
    if(getArenaSymbol(newPosition) == ' ')
    {
        renderChar(newPosition, laserOrientationSymbol.at(orientation));
    }

    currPosition = newPosition;
    reRenderAllPlayers();
}

void GameRenderer::renderLaserRemoved(ID laserID)
{
    const auto& laserPosition = lasers.at(laserID);
    reRerenderArenaLocation(laserPosition);
    lasers.erase(laserID);
    reRenderAllPlayers();
}

void GameRenderer::reRenderPlayer(ID playerID)
{
    wattron(window, COLOR_PAIR(playerColor.at(playerID)));
    renderChar(playerPositions.at(playerID), playerSymbols.at(playerID));
    wattroff(window, COLOR_PAIR(playerColor.at(playerID)));
}

void GameRenderer::reRenderAllPlayers()
{
    for(auto iter = playerPositions.begin(); iter != playerPositions.end(); ++iter)
    {
        reRenderPlayer(iter->first);
    }
}

void GameRenderer::renderPlayerScore(ID playerID, int score)
{
    const auto& scorePosition = playerScorePositions.at(playerID);
    auto scoreString = std::to_string(score);
    wattron(window, COLOR_PAIR(4));
    mvwprintw(window, scorePosition.y, scorePosition.x, scoreString.c_str());
    wattroff(window, COLOR_PAIR(4));
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
    wattron(window, COLOR_PAIR(4));
    mvwprintw(window, printY, printX, clearString.c_str());
    mvwprintw(window, printY, printX, secondsLeftStr.c_str());
    wattroff(window, COLOR_PAIR(4));
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
