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
        // rgba
        250,
        155,
        0,
        255,
        // line length and step size
        1000,
        3,
        // seed point counts for x, y
        50,
        50,
        false
    };
    FlowPreset cyanRivers
    {
        CyanRivers,
        0,
        100,
        100,
        10,
        10000,
        1,
        70,
        70,
        true
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
        50,       // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
        false
        /////////////////////////////////////////////////////////////////////////////////////////////////
    };

    while (window.isOpen())
    {
        window.clear();
        //window.clear(sf::Color::White);
        window.pollEvents();

        //window.drawTileMapsBack();
        //window.drawSprites();
        //window.drawTileMapsFront();
        window.drawSimplex();
        //window.drawFlow(inProgress);
        //window.drawFlow(cyanRivers);
        //window.drawFlow(dragonFlame);
        //window.drawParticles();

        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1160 fps
        window.display();
    }
    return 0;
}