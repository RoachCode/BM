#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"

extern class Window : public sf::RenderWindow
{
public:
	// Inherit constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	// Get the size of the window
	sf::Vector2u size;
	// Declare the view
	sf::View view;
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	Window();
	void pollEvents();
};