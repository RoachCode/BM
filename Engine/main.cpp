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
        255,
        // line length and step size
        400,
        10,
        // seed point counts for x, y
        20,
        20,
        false
    };
    FlowPreset cyanRivers
    {
        CyanRivers,
        0,
        100,
        100,
        10,
        1000,
        1,
        70,
        70,
        false
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









        // PRESS THE HOLLOW PLAY BUTTON ABOVE TO RUN   ▷   ESC to exit, or CTRL-ALT-DEL sometimes...
        // ALTERNATIVELY, PRESS CTRL-F5

        //window.drawTileMapsBack(); // 620
        //window.drawSprites(); // 1050
        //window.drawTileMapsFront(); // 620
        window.drawSimplex(); // 160
        //window.drawSimplex(UP);
        //window.drawSimplex(DOWN);
        //window.drawSimplex(LEFT);
        //window.drawSimplex(RIGHT);
        //window.drawFlow(inProgress);
        //window.drawFlow(cyanRivers);
        //window.drawFlow(dragonFlame);
        //window.drawParticles(sf::Color(255, 255, 255, 30));








        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50)); // 1100 - 1200 fps

        window.display();
    }
    return 0;
}