#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "constExpressions.h"
#include "font.h"
#include "devtools.h"
#include "imageHandler.h"
#include "character.h"
#include "noise.h"
#include "flow.h"
#include "particles.h"
#include "water.h"
#include "maps.h"

class Window : public sf::RenderWindow, public Noise
{
public:
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	Window();

	// Get the size of the window
	sf::Vector2u size;
	sf::Vector2i uniqueScreenSizeGridSize;
	int pixelSize{ 1 };
	int tileSize{};

	// Declare the view
	sf::View view;
	sf::Vector2f movementOffset;
	bool movementAllowed;
	bool lastKeyUp{ false };
	bool lastKeyDown{ false };
	bool lastKeyLeft{ false };
	bool lastKeyRight{ false };
	bool up{};
	bool down{};
	bool left{};
	bool right{};

	// Holds all sprites
	std::vector<sf::Sprite> spriteVector;

	// Create class instances
	Flow flow;
		int pathCounter{ 0 }; //?
		unsigned int dotCounter{ 0 }; //?
		int lineCounter{ 0 }; // ?
	ParticleSystem particles{ 30000 }; // Just for testing it out.
	Water water;

	Character arson{ intify(CharacterID::ArsonID) };
	Character gaia{ intify(CharacterID::GaiaID) };
	Character cole{ intify(CharacterID::ColeID) };
	Character neko{ intify(CharacterID::NekoID) };

	ImageHandler imageHandler;
	DevTools DEV_TOOLS;
	Font2 font;

	// Screenshot
	bool onlyOnceHack{ true };

	// Logic
	void pollEvents();
	void refreshMovementBools();
	Character& getCharacterByOrder(int order);
	void pollMovement();
	void startViewMovement(sf::Vector2f offset);
	void endViewMovement();

	void drawTileMapsBack();
	void drawFlow(FlowPreset& fp);
	void drawFlow();
	void drawParticles();
	void drawParticles(sf::Color color);
	void drawSprites();
	void drawWaterTile();
	void drawTileMapsFront();
	void drawFullSimplex(sf::Vector2f direction = sf::Vector2f(1, 0), int speed = 0);

	void drawText(std::string string, sf::Vector2f startPosition = sf::Vector2f(50.f, 50.f), int scale = 1);

	void m_groupDraw(sf::Vector2f direction);
	void m_groupDraw(int dirX, int dirY);
	void m_groupDraw();

	sf::Vector2f getViewCoordinates(int dir);

	sf::Vector2i getGridPosition();
	void changeFalseLastKeyState(bool& lastKeyInput);
	void sortSpriteVectorByHeight();
	void setPositionAndDraw(float x, float y);
	void checkUnderlyingTile(int dir);
	void setGameIcon();
	void setpixelSize(float factor = 1.2f);
	void moveViewByCharacter();
	void moveCharacters();
	void drawDevToolsText();

};
