#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "constExpressions.h"
#include "font.h"
#include "devtools.h"
#include "imageHandler.h"
#include "sprite.h"
#include "OpenSimplexNoise.h"
#include "flow.h"
#include "particles.h"
#include "water.h"
#include "maps.h"

extern class Window : public sf::RenderWindow
{
public:
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	Window();

	// Get the size of the window
	sf::Vector2u size;
	int windowScale{ 1 };

	// Declare the view
	sf::View view;
	sf::Vector2f movementOffset;
	bool isMovingView;

	// Data containers
	std::vector<float> angleVector;
	std::vector<int> tempContainer;
	std::deque<sf::Uint8> simplexData;
	std::vector<float> xyValues;

	// Create class instances
	Flow flow;
		int pathCounter{ 0 }; //?
		unsigned int dotCounter{ 0 }; //?
		int lineCounter{ 0 }; // ?
	ParticleSystem particles{ 30000 }; // Just for testing it out.
	Water water;
	Sprite sprite;
	ImageHandler imageHandler;
	DevTools DEV_TOOLS;
	Font2 font;

	// Other Simplex Noise variables
	int simplexSizeX;
	int simplexSizeY;
	int simplexSpeed;
	int simplexStepper;
	int simplexOctaves{};
	sf::RectangleShape noise;
	sf::Texture noiseTexture;

	// Screenshot
	bool onlyOnceHack{ true };

	// Logic
	void pollEvents();
	void pollMovement();
	void startViewMovement(sf::Vector2f offset);
	void endViewMovement();

	void drawTileMapsBack();
	void drawFlow(FlowPreset& fp);
	void drawParticles();
	void drawParticles(sf::Color color);
	void drawSprites();
	void drawWaterTile();
	void drawTileMapsFront();
	void drawFullSimplex(sf::Vector2f direction = sf::Vector2f(1, 0), int speed = 0);
		void initSimplex(float sizeX, float sizeY, int octaves);
		void createSimplexValues(int x, int y);
		void normalizeRGB();
		void createSimplexTexture();
		void m_groupDraw();
		void m_groupDraw(sf::Vector2f direction);
		void m_groupDraw(int dirX, int dirY);
	void drawText(std::string string, sf::Vector2f startPosition = sf::Vector2f(50.f, 50.f));

private:

};
