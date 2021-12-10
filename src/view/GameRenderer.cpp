#include "GameRenderer.h"

GameRenderer::GameRenderer(WINDOW* window): 
    window(window)
{
    playerSymbols[0] = '@';
    playerSymbols[1] = '&';
}

void GameRenderer::renderPlayerFirstTime(int playerID, Vector2d newPosition)
{
    playerPositions[playerID] = newPosition;
    mvwaddch(window, newPosition.y, newPosition.x, playerSymbols[playerID]);
}

void GameRenderer::renderPlayer(int playerID, Vector2d newPosition)
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

void GameRenderer::renderLaserFirstTime(int laserID, Vector2d newPosition, LaserOrientation orientation)
{

}

void GameRenderer::renderLaser(int laserID, Vector2d newPosition, LaserOrientation orientation)
{

}

void GameRenderer::removeLaser(int laserID)
{

}
