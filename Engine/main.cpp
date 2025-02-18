#pragma once
#include "window.h"


// Test Globals
sf::RenderTexture lightRender, pass_normals, pass_diffuse;
sf::Texture normal_map, diffuse_map;
sf::Sprite spriteT;

void loadLightTest(Window &window)
{
	int width{ intify(View::getSceneSize().x * View::getPixelSize()) };
	int height{ intify(View::getSceneSize().y * View::getPixelSize()) };

	//back.create(width, height);
	lightRender.create(View::getScreenSize().x, View::getScreenSize().y);
	pass_normals.create(width, height);
	pass_diffuse.create(width, height);

	//normal_map.loadFromFile("C:/Users/Windows/Desktop/normal_mapping_normal_map.png");
	//diffuse_map.loadFromFile("C:/Users/Windows/Desktop/brickwall.jpg");

	normal_map = window.imageHandler.normalsRender.getTexture();
	diffuse_map = window.imageHandler.tilemapRenderBack.getTexture();

	spriteT.setTexture(diffuse_map);
	spriteT.setScale(pairF(View::getPixelSize(), View::getPixelSize()));

	// Clear to neutral color
	pass_normals.clear(sf::Color(128, 128, 255));
	pass_diffuse.clear(sf::Color(128, 128, 255));
	lightRender.clear();

	// Normals Pass, feed every normal map which should be rendered here
	// For more then one repeat the next 2 steps before displaying
	window.imageHandler.normals_shader.setUniform("sampler_normal", normal_map);
	pass_normals.draw(spriteT, &window.imageHandler.normals_shader);
	pass_normals.display();

	// Diffuse Pass, feed every sprite to draw here before display
	pass_diffuse.draw(spriteT);
	pass_diffuse.display();

	// Light Pass, renders every light into a rendertexture
	window.imageHandler.lights_shader.setUniform("resolution", sf::Vector2f(View::getScreenSize().x, View::getScreenSize().y));
	window.imageHandler.lights_shader.setUniform("sampler_normal", pass_normals.getTexture());
	window.imageHandler.lights_shader.setUniform("sampler_light", lightRender.getTexture());
	window.imageHandler.lights_shader.setUniform("ambient_intensity", window.imageHandler.light.ambientIntensity);
	window.imageHandler.lights_shader.setUniform("falloff", window.imageHandler.light.falloff);
	window.imageHandler.lights_shader.setUniform("light_color", window.imageHandler.light.color);
}
void drawLightTest(Window& window)
{
	//window.imageHandler.light.position.x = sf::Mouse::getPosition(window).x;
	//window.imageHandler.light.position.y = View::getScreenSize().y - sf::Mouse::getPosition(window).y;
	float offset = (TILE_SIZE / 2) * View::getPixelSize();
	sf::Vector2f charPos = window.getCharacterByOrder(1).sprite.getPosition();
	window.imageHandler.light.position.x = charPos.x + offset - View::getOriginOffset().x;
	window.imageHandler.light.position.y = View::getScreenSize().y - charPos.y - offset + View::getOriginOffset().y;
	
	window.imageHandler.lights_shader.setUniform("light_pos", window.imageHandler.light.position);
	window.draw(sf::Sprite(pass_diffuse.getTexture()), &window.imageHandler.lights_shader);
	window.draw(sf::Sprite(pass_diffuse.getTexture()), sf::BlendMultiply);
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
	window.setVerticalSyncEnabled(true); // disable to see true, unhindered loop time in ms

	loadLightTest(window);

	window.setMouseCursorVisible(false);
    while (window.isOpen())
    {
        window.clear(sf::Color(50, 0, 50, 255));
        window.pollEvents();

        //window.drawTileMapsBack();
		drawLightTest(window);		
		window.drawSprites();
		//window.drawLights();

		//window.drawParticles(sf::Color(255, 255, 255, 30)); // quite slow, even when not drawing. fixit.
        //window.drawFlow(cyanRivers);

        //window.drawWaterTile();
        //window.drawTileMapsFront();
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
