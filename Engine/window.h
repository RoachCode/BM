#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "constExpressions.h"
#include "font.h"
#include "devtools.h"
#include "imageHandler.h"
#include "sprite.h"
#include "PerlinNoise.hpp"

extern class Window : public sf::RenderWindow
{
public:
	Sprite sprite;
	sf::RenderTexture renderWindowSprites;
	sf::RectangleShape pseudoWindowSprites;

	ImageHandler imageHandler;
	void drawTileMapsBack();
	void drawTileMapsFront();
	DevTools DEV_TOOLS;
	Font2 font;
	// Inherit constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	// Get the size of the window
	sf::Vector2u size;
	// Declare the view
	sf::View view;
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	Window();
	void pollEvents();
	void drawText(std::string string, sf::Vector2f startPosition = sf::Vector2f(50.f, 50.f));
	void startViewMovement(sf::Vector2f offset);
	void endViewMovement();
	bool isMovingView;
	sf::Vector2f movementOffset;
	void pollMovement();
	void drawSprites();
	void drawParticles();
	void drawPerlin();
	int perlinCounter;
	std::deque<sf::Uint8> perlinData;
	sf::RectangleShape noise;
	sf::Texture noiseTexture;

	void initPerlin();

private:
	int getZoomFactor();
};