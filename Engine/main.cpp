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
        //window.drawTileMapsBack();
        //window.drawSprites();
        //window.drawTileMapsFront();
        //window.drawSimplex();

        window.drawFlow(31, 31);
        //window.drawParticles();


        //pathing.setPosition(0, 0);?
        //window.drawParticles(); // can get expensive depending on particlecount


        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1160 fps

        window.display();
        
        //sf::sleep(sf::milliseconds(20000));
    }

    return 0;
}