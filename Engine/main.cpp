#pragma once
#include "window.h"


int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(255, 120, 10));

    
    
    while (window.isOpen())
    {
        //window.close();
        window.clear();

        window.pollEvents();
        window.drawTileMapsBack();
        //window.drawSprites();
        window.drawTileMapsFront();

        window.drawSimplex();
        window.drawParticles();


        //window.draw(noise);
        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
      
        window.display();

    }

    return 0;
}