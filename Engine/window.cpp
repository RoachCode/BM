#pragma once
#include "constExpressions.h"
#include "window.h"

// Call constructor, which calls inherited constructor from sf::RenderWindow
Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	// Get the size of the window
	Window::size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	// Sets the view to the appropriate zoom level for display
	Window::view = this->getDefaultView();
	while (Window::view.getSize().x > MAP_WIDTH * 2)
	{
		Window::view.setSize(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
		Window::view.setCenter(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
	}
	this->setView(Window::view);

	//

}
