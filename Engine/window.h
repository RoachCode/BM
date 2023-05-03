#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "font.h"

extern class Window : public sf::RenderWindow
{
public:
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
private:
	int getZoomFactor();
};