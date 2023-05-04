#pragma once
#include "window.h"

int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(155, 0, 0));
    while (window.isOpen())
    {
        window.clear();

        window.pollEvents();
        window.drawTileMaps();
        window.drawSprites();
        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
      
        window.display();

    }

    return 0;
}