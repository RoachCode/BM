#pragma once
#include "window.h"

int main()
{
    Window window;
	//FlowPresets
#pragma region
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
			30,
			1
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
		30,
		1
	};
	FlowPreset inProgress
	{
		InProgress,
		//////////////////////////////////////////////////////////////////////////////////////////////////
		255,        // red   ----------- [125, 255]
		0,          // green ----------- [025, 255]
		0,          // blue  ----------- [125, 255]
		40,         // alpha ----------- [0, 255]
		200,        // line length ----- [1, 1000000] BIG NUMBERS MAKE LINES LONG AND RENDERING SLOW.
		floatify(window.pixelSize * 4),   // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
		4,          // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
		8,          // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
		4
		/////////////////////////////////////////////////////////////////////////////////////////////////
	};
#pragma endregion
	//window.DEV_TOOLS.toggleFreeMovement();
	window.setVerticalSyncEnabled(true); // disable to see true, unhindered loop time in ms
    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0, 255));
        window.pollEvents();

        window.drawTileMapsBack(); // 620
		//window.drawParticles(sf::Color(255, 255, 255, 30));
		window.drawSprites(); // 1050
        //window.drawFlow(inProgress);
        window.drawWaterTile();
        window.drawTileMapsFront(); // 620

        window.drawFullSimplex(sf::Vector2f(0, -0.45), 0); // 520. if speed is needed we can jump frames         x = -0.8
		window.drawDevToolsText();

		window.display();
    }
    return 0;
}