#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "constExpressions.h"
#include "font.h"
#include "devtools.h"
#include "imageHandler.h"
#include "sprite.h"
#include "OpenSimplexNoise.h"
#include "particles.h"
#include "flow.h"

extern class Window : public sf::RenderWindow
{
public:
	int windowScale{ 1 };
	std::vector<float> angleVector;
	Flow flow;
	ParticleSystem particles{ 30000, flow }; // Just for testing it out.

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
	std::vector<int> tempContainer;
	void pollEvents();
	void drawText(std::string string, sf::Vector2f startPosition = sf::Vector2f(50.f, 50.f));
	void startViewMovement(sf::Vector2f offset);
	void endViewMovement();
	bool isMovingView;
	sf::Vector2f movementOffset;
	void pollMovement();
	void drawSprites();
	void drawParticles();

	float simplexSizeX;
	float simplexSizeY;
	void drawSimplex(int direction = -1);
	int simplexSpeed;
	std::deque<sf::Uint8> simplexData;
	sf::RectangleShape noise;
	sf::Texture noiseTexture;
	void drawFlow(FlowPreset &fp);
	void initSimplex(float sizeX, float sizeY, int octaves);
	std::vector<float> xyValues;
	int simplexOctaves{};
	void createSimplexValues(int x, int y);
	void normalizeRGB();



	int pathCounter{ 0 };
	unsigned int dotCounter{ 0 };
	bool drawGrid{ false };
	bool drawNeedles{ false };
	bool drawLines{ true };

	sf::RenderTexture flowWindowTexture;
	sf::RectangleShape flowWindow;
	bool onlyOnceHack{ true };
private:


};
