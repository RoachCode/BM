#pragma once
#include <SFML/Graphics.hpp>

extern class DevTools
{
private:
	int getFPS();
public:
	sf::Clock clock;
	sf::Time time;
	int counter;
	void showFPS();
	DevTools();
};