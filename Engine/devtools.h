#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern class DevTools
{
private:
	// Returns the FPS or zero
	void calculateFPS();
	// Iterates to count FPS
	int counter;
	int fps;
	sf::Clock clock;
	sf::Time time;

public:
	DevTools();
	// returns FPS as a std::string.
	std::string getFPS();
	// Logs to the console adding a line break after, using auto.
	void log(auto in);
};