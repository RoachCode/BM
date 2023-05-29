#pragma once
#include "window.h"

int main()
{
    Window window;
    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0, 255));
        window.pollEvents();
/*

        window.drawFlow(inProgress);
        window.drawFlow(cyanRivers);
        window.drawFlow(dragonFlame);
        window.drawParticles(sf::Color(255, 255, 255, 30));
        window.drawSprites(); // 1050

      
*/
        window.drawTileMapsBack(); // 620
        window.drawWaterTile();
        window.drawTileMapsFront(); // 620
        window.drawFullSimplex(sf::Vector2f(-1, 0), 3); // 160. if speed is needed we can jump frames  






        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1100 - 1200 fps
        window.display();
    }
    return 0;
}