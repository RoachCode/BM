#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define DEBUG(a) std::cerr << #a << ": " << (a) << '\n'

class DevTools
{
public:
	// Constructor
	DevTools();

	// Query the m_freeMovementAllowed bool
	const bool queryFreeMovement();

	// Toggle the m_freeMovementAllowed bool
	void toggleFreeMovement();

	// returns FPS as a std::string.
	const std::string getFPS();

	// Logs to the console adding a line break after, using std::string.
	template <typename T>
	constexpr void log(T const& in = "Error: Nothing Found");

	// Toggles wallToggleBool
	bool wallToggleBool;
	void wallToggle();
private:
	// Runs the m_counter and m_clock and sets the m_fps value
	void m_calculateFPS();

	// FPS calculation variables
	sf::Clock m_clock;
	int m_counter;
	int m_fps;

	// Free camera movement bool
	bool m_freeMovementAllowed;
};