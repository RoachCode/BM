#pragma once
#include <SFML/Graphics.hpp>
#include "textbox.h"
#include "view.h"

class Menu : protected View
{
private:
	bool enabled;
	sf::Clock clock;
	int offset;
	int width;
	int height;
	sf::Vector2f pos;

public:
	TextBox menuBox;
	TextBox alertBox;

	Menu()
	{
		enabled = false;
		offset = View::getPixelSize() * 4 + menuBox.box.lineThickness;
		width = View::getScreenSize().x - offset * 2;
		height = View::getScreenSize().y - offset * 2 - menuBox.box.borderOffset;
	}

	void toggleMenu() { enabled = !enabled; }
	bool menuEnabled() const { return enabled; }

	void createMenu()
	{
		// background container
		pos = pairF(View::getViewCoordinates(UL).x + offset, View::getViewCoordinates(UL).y + offset);
		menuBox.box.createBackground(pos, width, height);
		menuBox.box.createBorders(pos, width, height);


	}
};