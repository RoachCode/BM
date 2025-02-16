#pragma once
#pragma warning( disable : 4018 ) // signed/unsigned mismatch in conditionals is OK.
#include <SFML/Graphics.hpp>
#include <deque>
#include "constExpressions.h"
#include "view.h"
#include "menu.h"
#include "devtools.h"
#include "imageHandler.h"
#include "character.h"
#include "noise.h"
#include "flow.h"
#include "particles.h"
#include "water.h"
#include "maps.h"
#include "textbox.h"
#include "light.h"

class Window : public sf::RenderWindow, public Noise, public View
{
public:
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	Window();

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
	TextBox textBox;
	TextBox importantTextBox;
	Menu menu;

	// Screenshot
	bool onlyOnceHack{ true };

	// Logic
	void pollEvents();
	void refreshMovementBools();
	Character& getCharacterByOrder(int order);
	void pollMovement();

	void drawTileMapsBack();
	void drawFlow(FlowPreset& fp);
	void drawFlow();
	void drawParticles();
	void drawParticles(sf::Color color);
	void drawSprites();
	void drawWaterTile();
	void drawTileMapsFront();
	void drawFullSimplex(sf::Vector2f direction = sf::Vector2f(0.f, 0.f));
	void drawMenu();

	void addText(
		std::string string = "NOTEXT", 
		sf::Vector2f startPosition = sf::Vector2f(0.f, 0.f), 
		int scale = 1, 
		int boundingWidth = 0,
		bool background = true,
		bool borders = true,
		bool important = false
	);
	void drawText();

	void m_groupDraw(sf::Vector2f direction);
	void m_groupDraw(int dirX, int dirY);
	void m_groupDraw();

	sf::Vector2i getGridPosition();
	void changeFalseLastKeyState(bool& lastKeyInput);
	void sortSpriteVectorByHeight();
	void setPositionAndDraw(float x, float y);
	void checkUnderlyingTile();
	void setGameIcon();

	void moveCharacters();
	void addDevToolsText();
	//void initWaterTile();
	void drawLights();
	void drawTest();
	void makeTest();
};
