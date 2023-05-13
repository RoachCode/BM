#pragma once
#include "window.h"


int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(255, 120, 10));

    bool onlyOnceHack{ true };

    while (window.isOpen())
    {
        //window.close();
        window.clear();

        window.pollEvents();
        //window.drawTileMapsBack();
        //window.drawSprites();
        //window.drawTileMapsFront();
        //window.drawSimplex();

        window.drawFlow(100, 100);
        //window.drawParticles();


        //pathing.setPosition(0, 0);?
        //window.drawParticles(); // can get expensive depending on particlecount


        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1160 fps


        if (onlyOnceHack)
        {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);

            if (!texture.copyToImage().saveToFile("abadaba.png"))
            {
                std::cout << "screenshot failed";
            }
            onlyOnceHack = false;
        }
        window.display();

        //window.close();
        //sf::sleep(sf::milliseconds(2000));
       
        
    }

    return 0;
}