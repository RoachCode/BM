#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern class DevTools
{
private:
	// Returns the FPS or zero
	int calculateFPS();
	// Iterates to count FPS
	int counter;
	sf::Clock clock;
	sf::Time time;

public:
	DevTools();
	// returns FPS.
	int getFPS();
	// Logs to the console adding a line break after, using auto.
	void log(auto in);
};