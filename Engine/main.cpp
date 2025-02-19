#pragma once
#include "window.h"


// Test Globals


void drawLightTest(Window& window)
{
	window.imageHandler.light.position.x = sf::Mouse::getPosition(window).x;
	window.imageHandler.light.position.y = View::getScreenSize().y - sf::Mouse::getPosition(window).y;
	//float offset = (TILE_SIZE / 2) * View::getPixelSize();
	//sf::Vector2f charPos = window.getCharacterByOrder(1).sprite.getPosition();
	//window.imageHandler.light.position.x = charPos.x + offset - View::getOriginOffset().x;
	//window.imageHandler.light.position.y = View::getScreenSize().y - charPos.y - offset + View::getOriginOffset().y;
	window.imageHandler.lights_shader.setUniform("light_pos", window.imageHandler.light.position);

	sf::RenderStates states;
	states.blendMode = sf::BlendMultiply;
	states.shader = &window.imageHandler.lights_shader;
	window.draw(sf::Sprite(window.imageHandler.tilemapRenderBack.getTexture()), states);

}

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
		floatify(window.getPixelSize() * 4),   // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
		4,          // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
		8,          // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
		4
		/////////////////////////////////////////////////////////////////////////////////////////////////
	};
#pragma endregion
	//window.DEV_TOOLS.toggleFreeMovement();
	//window.setVerticalSyncEnabled(true); // disable to see true, unhindered loop time in ms

	//window.setMouseCursorVisible(false);
    while (window.isOpen())
    {
        window.clear(sf::Color(50, 0, 50, 255));
        window.pollEvents();
		//window.drawParticles(sf::Color(255, 255, 255, 30)); // quite slow, even when not drawing. fixit.
        //window.drawFlow(cyanRivers);




        window.drawTileMapsBack();
		//window.drawSprites();
        //window.drawWaterTile();
        window.drawTileMapsFront();
		drawLightTest(window);




        //window.drawFullSimplex(sf::Vector2f(-1.f, -0.35f));
		window.addDevToolsText();
		//window.drawText();

		//window.drawMenu();
		//window.drawBattle();

		window.drawText();
		window.display();
    }
    return EXIT_SUCCESS;
}
