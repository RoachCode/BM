#pragma once
#include "window.h"


int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(255, 120, 10));

    static bool onlyOnceHack{ true };

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
        window.display();


        sf::Texture texture;
        texture.create(window.flow.gridSize.x, window.flow.gridSize.y);

        if (onlyOnceHack)
        {
            for (int i = 0; i < 10; i++)
            {
                const int idx = i;
                std::string filename = "abadaba" + std::to_string(idx) + ".png";
                texture.update(window, window.flow.gridSize.x, window.flow.gridSize.y);
                if (texture.copyToImage().saveToFile(filename))
                {
                    std::cout << "screenshot saved to " << "abadaba" << std::endl;
                }
            }


            onlyOnceHack = false;
        }


        //window.close();
        sf::sleep(sf::milliseconds(2000));
       
        
    }

    return 0;
}