#include "GameRenderer.h"

GameRenderer::GameRenderer(WINDOW* window): 
    window(window)
{
    playerSymbols[0] = '@';
    playerSymbols[1] = '&';
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

void GameRenderer::renderArena(const Arena& arena)
{
    for (size_t y_index = 0; y_index < arena.getYmax(); y_index++)
    {
        for (size_t x_index = 0; x_index < arena.getXmax(); x_index++)
        {
            if(arena.at(x_index, y_index) == ObstacleType::OBSTACLE)
            {
                mvwaddch(window, y_index, x_index, 'o');
            }
        }
    }
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
