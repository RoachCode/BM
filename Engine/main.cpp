#pragma once
#include "window.h"

FlowPreset dragonFlame
{
	DragonFlame,
		250,
		155,
		5,
		160,
		100,
		1,
		40,
		30
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

	200,
	30
};
FlowPreset inProgress
{
	InProgress,
	//////////////////////////////////////////////////////////////////////////////////////////////////
	0,        // red   ----------- [125, 255]
	200,      // green ----------- [025, 255]
	200,      // blue  ----------- [125, 255]
	40,       // alpha ----------- [0, 255]
	2000,     // line length ----- [1, 1000000] BIG NUMBERS MAKE LINES LONG AND RENDERING SLOW.
	0.25,     // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
	8,        // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
	1         // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
	/////////////////////////////////////////////////////////////////////////////////////////////////
};


int main()
{
    Window window;
	//window.DEV_TOOLS.toggleFreeMovement();
	//window.view.zoom(2);
	window.setVerticalSyncEnabled(true); // disable to see true, unhindered loop time in ms
    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0, 255));
        window.pollEvents();

        window.drawTileMapsBack(); // 620
	    //window.drawFlow();
		//window.drawParticles(sf::Color(255, 255, 255, 30));
		window.drawSprites(); // 1050
        //window.drawFlow(cyanRivers);
        window.drawTileMapsFront(); // 620
        window.drawWaterTile();
        //window.drawFullSimplex(sf::Vector2f(0, -0.45), 0); // 160. if speed is needed we can jump frames         x = -0.8     
        window.drawText(
			window.DEV_TOOLS.getFPS(), 
			sf::Vector2f(window.getTopLeftViewCoordinates().x + window.getSize().x - 64, 
			window.getTopLeftViewCoordinates().y + 50)
		); // 1100 - 1200 fps
		window.drawText(
			"X" + std::to_string(intify(window.getGridPosition().x)) + 
			" Y" + std::to_string(intify(window.getGridPosition().y)), 
			sf::Vector2f(window.getTopLeftViewCoordinates().x + 
			window.getSize().x - 111, window.getTopLeftViewCoordinates().y + 8)
		);

        window.display();
    }
    return 0;
}