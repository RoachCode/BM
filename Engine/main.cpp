#pragma once
#include "window.h"
#include "particles.h"
int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(80, 0, 144));

    ParticleSystem particles(50000); // Just for testing it out.

    while (window.isOpen())
    {
        window.clear();

        window.pollEvents();
        window.drawTileMapsBack();
        window.drawSprites();
        window.drawTileMapsFront();
        //window.drawParticles();


        //particle system test
        /*
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));
        sf::Time elapsed = particles.clock.restart();
        particles.update(elapsed);
        window.draw(particles);
        */

        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
      
        window.display();

    }

    return 0;
}