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
        5,
        160,
        // line length and step size
        400,
        4,
        // seed point counts for x, y
        40,
        30,
    };
    FlowPreset cyanRivers
    {
        CyanRivers,

        0,
        100,
        100,
        10,

        600,
        1,

        20,
        30
    };
    FlowPreset inProgress
    {
        InProgress,
        //////////////////////////////////////////////////////////////////////////////////////////////////
        0,      // red   ----------- [125, 255]
        200,    // green ----------- [025, 255]
        0,      // blue  ----------- [125, 255]
        15,     // alpha ----------- [0, 255]
        1000,   // line length ----- [1, 1000000] BIG NUMBERS MAKE LINES LONG AND RENDERING SLOW.
        10,      // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
        50,      // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
        50       // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
        /////////////////////////////////////////////////////////////////////////////////////////////////
    };

    while (window.isOpen())
    {
        window.clear();
        //window.clear(sf::Color::White);
        window.pollEvents();









        // PRESS THE HOLLOW PLAY BUTTON ABOVE TO RUN   ▷   ESC to exit, or CTRL-ALT-DEL sometimes...
        // ALTERNATIVELY, PRESS CTRL-F5

        //window.drawTileMapsBack(); // 620
        //window.drawSprites(); // 1050
        //window.drawTileMapsFront(); // 620
        //window.drawFullSimplex(LEFT, 1); // 160. if speed is needed we can jump frames
        //window.drawFlow(dragonFlame);
        window.drawFlow(cyanRivers);
        //window.drawFlow(cyanRivers);
        //window.drawFlow(dragonFlame);
        //window.drawParticles(sf::Color(255, 255, 255, 30));








        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1100 - 1200 fps

        window.display();
    }
    return 0;
}