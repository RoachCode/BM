#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Window : public sf::RenderWindow
{
public:
	// Inherit constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	Window(sf::VideoMode vm, char tit[])
		: sf::RenderWindow(vm, tit)
	{
		// further construction
	}
};
