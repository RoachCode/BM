#pragma once
#include "window.h"


int main()
{
    ImageHandler imageHandler;
    Window window;
	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(255, 120, 10));

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
    FlowPreset inProgress
    {
        InProgress,
        //////////////////////////////////////////////////////////////////////////////////////////////////
        0,      // red   ----------- [125, 255]
        200,    // green ----------- [025, 255]
        0,      // blue  ----------- [125, 255]
        5,     // alpha ----------- [0, 255]
        1000,   // line length ----- [1, 1000000] BIG NUMBERS MAKE LINES LONG AND RENDERING SLOW.
        10,      // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
        50,      // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
        50       // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
        /////////////////////////////////////////////////////////////////////////////////////////////////
    };

    while (window.isOpen())
    {
        //window.close();
        window.clear();

        window.pollEvents();
        //window.drawTileMapsBack();
        //window.drawSprites();
        //window.drawTileMapsFront();
        //window.drawSimplex(RIGHT);

        window.drawFlow(inProgress);
        //window.drawParticles();


        //pathing.setPosition(0, 0);?
        //window.drawParticles(); // can get expensive depending on particlecount


        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1160 fps
        



        window.display();
    }

    return 0;
}