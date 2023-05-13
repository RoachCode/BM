#pragma once
#include "window.h"


int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(255, 120, 10));

    bool onlyOnceHack{ true };

    FlowPreset dragonFlame
    {
        DragonFlame,
        250,
        155,
        0,
        100,
        290,
        0.5,
        70,
        70
    };
    FlowPreset cyanRivers
    {
        CyanRivers,
        0,
        100,
        100,
        15,
        10000,
        1,
        70,
        70
    };

    while (window.isOpen())
    {
        //window.close();
        window.clear(sf::Color::White);

        window.pollEvents();
        //window.drawTileMapsBack();
        //window.drawSprites();
        //window.drawTileMapsFront();
        //window.drawSimplex();


        window.drawFlow(dragonFlame);
        //window.drawParticles();


        //pathing.setPosition(0, 0);?
        //window.drawParticles(); // can get expensive depending on particlecount


        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1160 fps


        if (onlyOnceHack)
        {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);

            std::string filename = window.flow.currentName + ".bmp";
            if (!texture.copyToImage().saveToFile(filename))
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