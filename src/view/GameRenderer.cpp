#include "GameRenderer.h"

#include <string>

GameRenderer::GameRenderer(WINDOW* window): 
    window(window)
{
    playerSymbols.insert({0, '@'});
    playerSymbols.insert({1, '&'});

    int y, x;
    getmaxyx(window, y, x);
    playerScorePositions.emplace(0, Vector2d(0, y-1));
    playerScorePositions.emplace(1, Vector2d(x-2, y-1));
}

void GameRenderer::renderPlayerFirstTime(ID playerID, Vector2d newPosition)
{
    playerPositions[playerID] = newPosition;
    mvwaddch(window, newPosition.y, newPosition.x, playerSymbols[playerID]);
}

void GameRenderer::renderPlayer(ID playerID, Vector2d newPosition)
{
    auto& currPosition = playerPositions[playerID];
    mvwaddch(window, currPosition.y, currPosition.x, ' ');
    mvwaddch(window, newPosition.y, newPosition.x, playerSymbols[playerID]);
    currPosition = newPosition;
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
    for (int y_index = 0; y_index < arena.getYmax(); y_index++)
    {
        for (int x_index = 0; x_index < arena.getXmax(); x_index++)
        {
            if(arena.at(x_index, y_index) == ObstacleType::OBSTACLE)
            {
                mvwaddch(window, y_index, x_index, 'o');
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

void GameRenderer::renderLaserFirstTime(ID laserID, Vector2d newPosition, LaserOrientation orientation)
{
    lasers[laserID] = newPosition;
    mvwaddch(window, newPosition.y, newPosition.x, laserOrientationSymbol.at(orientation));
}

void GameRenderer::renderLaser(ID laserID, Vector2d newPosition, LaserOrientation orientation)
{
    auto& currPosition = lasers.at(laserID);
    mvwaddch(window, currPosition.y, currPosition.x, ' ');
    mvwaddch(window, newPosition.y, newPosition.x, laserOrientationSymbol.at(orientation));
    currPosition = newPosition;
}

void GameRenderer::removeLaser(ID laserID)
{
    const auto& laserPosition = lasers.at(laserID);
    mvwaddch(window, laserPosition.y, laserPosition.x, ' ');
    lasers.erase(laserID);
}
