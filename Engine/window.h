#pragma once
#include <SFML/Graphics.hpp>
//#include <iostream>
template <typename T>
constexpr float floatify(T const& value) { return static_cast<float>(value); }
constexpr unsigned int MAP_WIDTH{ 768 };
constexpr unsigned int MAP_HEIGHT{ 448 };

class Window : public sf::RenderWindow
{
public:
	// Inherit constructor from sf::RenderWindow
	using sf::RenderWindow::RenderWindow;
	// Get the size of the window
	const sf::Vector2u size{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
	// Declare the view
	sf::View view;
	// Call constructor, which calls inherited constructor from sf::RenderWindow
	Window()
		: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
	{
		// Sets the view to the appropriate zoom level for display
		view = this->getDefaultView();
		while (view.getSize().x > MAP_WIDTH * 2) 
		{
			view.setSize(floatify(view.getSize().x / 2), floatify(view.getSize().y / 2));
			view.setCenter(floatify(view.getSize().x / 2), floatify(view.getSize().y / 2));
		}
		this->setView(view);

		//

	}
};
