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
		floatify(window.getPixelSize() * 4),   // step size ------- [0.001, 10] OUTSIDE OF THESE BOUNDS WILL LOOK WEIRD. SMALLER IS BETTER RESOLUTION, AND SLOWER.
		4,          // num of lines wide [0, 300] BIG NUMBER MAKES IT SLOW
		8,          // num of lines high [0, 300] BIG NUMBER MAKES IT SLOW
		4
		/////////////////////////////////////////////////////////////////////////////////////////////////
	};
#pragma endregion
	//window.DEV_TOOLS.toggleFreeMovement();
	//window.setVerticalSyncEnabled(true); // disable to see true, unhindered loop time in ms


	int width{ intify(View::getScreenSize().x) };
	int height{ intify(View::getScreenSize().y) };

	sf::RenderTexture back, lightRender, pass_normals, pass_diffuse;
	sf::Texture normal_map, diffuse_map;

	back.create(width, height);
	lightRender.create(width, height);
	pass_normals.create(width, height);
	pass_diffuse.create(width, height);

	normal_map.loadFromFile("C:/Users/Windows/Desktop/brickwall_normal.jpg");
	diffuse_map.loadFromFile("C:/Users/Windows/Desktop/brickwall.jpg");

	sf::Sprite sprite(diffuse_map);

	sf::Shader lights_shader;
	sf::Shader normals_shader;

	Light light;

	const char lightFrag[] =
		"uniform vec2 resolution;"
		"uniform sampler2D sampler_normal;"
		"uniform sampler2D sampler_light;"
		"uniform vec3 light_pos;"
		"uniform vec3 light_color;"
		"uniform vec3 ambient_color = vec3(0.5, 0.5, 0.5);"
		"uniform float ambient_intensity;"
		"uniform vec3 falloff;"
		"void main()"
		"{"
		"vec2 coord = gl_TexCoord[0].xy;"
		"vec3 normal_map = texture2D(sampler_normal, coord).rgb;"
		"vec3 light_map = texture2D(sampler_light, coord).rgb;"
		"vec3 lightDir = vec3((light_pos.xy - gl_FragCoord.xy) / resolution.xy, light_pos.z); "
		"lightDir.x *= resolution.x / resolution.y;"
		"float D = length(lightDir);"
		"vec3 N = normalize(normal_map * 2.0 - 1.0);"
		//"vec3 N = -1.0 * normalize(normal_map * 2.0 - 1.0);"
		"vec3 L = normalize(lightDir.xyz);"
		"vec3 diffuse = light_color.rgb * max(dot(N, L), 0.0);"
		"vec3 ambient = ambient_color * ambient_intensity;"
		"float attenuation = 1.0 / (falloff.x + (falloff.y * D) + falloff.z * D * D);"
		"vec3 intensity = ambient + diffuse * attenuation;"
		"gl_FragColor = vec4(light_map + intensity, 1.0);"
		"}";

	const char normalsFrag[] =
		"uniform sampler2D sampler_normal;"
		"void main(void)"
		"{"
		"vec3 normal_map = texture2D(sampler_normal, gl_TexCoord[0].xy).rgb;"
		"gl_FragColor = vec4(normal_map, 1.0);"
		"}";

	lights_shader.loadFromMemory(lightFrag, sf::Shader::Fragment);
	sf::RenderStates states;
	states.shader = &lights_shader;
	states.blendMode = sf::BlendMultiply;
	normals_shader.loadFromMemory(normalsFrag, sf::Shader::Fragment);

	// Center Sprite
	sprite.setOrigin(diffuse_map.getSize().x / 2, diffuse_map.getSize().y / 2);
	sprite.setPosition(View::getView().getCenter());

	// Environmental variables



	window.setMouseCursorVisible(false);
    while (window.isOpen())
    {
        window.clear(sf::Color(50, 0, 50, 255));
        window.pollEvents();

        //window.drawTileMapsBack();
		//window.drawSprites();
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

		// Clear renderbuffers
		back.clear();
		lightRender.clear();
		pass_diffuse.clear();
		pass_normals.clear();

		// set light position, and adjust for different coordinate systems
		light.position.x = sf::Mouse::getPosition(window).x;
		light.position.y = height - sf::Mouse::getPosition(window).y;

		// Diffuse Pass, feed every sprite to draw here before display
		pass_diffuse.draw(sprite);

		// Normals Pass, feed every normal map which should be rendered here
		// For more then one repeat the next 2 steps before displaying
		normals_shader.setUniform("sampler_normal", normal_map);
		pass_normals.draw(sprite, &normals_shader);

		// Light Pass, renders every light into a rendertexture
		lights_shader.setUniform("resolution", sf::Vector2f(width, height));
		lights_shader.setUniform("sampler_normal", pass_normals.getTexture());
		lights_shader.setUniform("sampler_light", lightRender.getTexture());

		lights_shader.setUniform("ambient_intensity", light.ambientIntensity);
		lights_shader.setUniform("falloff", light.falloff);
		lights_shader.setUniform("light_pos", light.position);
		lights_shader.setUniform("light_color", light.color);
		back.draw(sf::Sprite(pass_diffuse.getTexture()), &lights_shader);

		// Draw diffuse color
		window.draw(sf::Sprite(pass_diffuse.getTexture()));
		// Blend lighting over
		back.display();
		window.draw(sf::Sprite(back.getTexture()), sf::BlendMultiply);


		window.drawText();
		window.display();
    }
    return EXIT_SUCCESS;
}