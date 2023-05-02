#pragma once
#include "window.h"

// Call constructor, which calls inherited constructor from sf::RenderWindow
Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	// Get the size of the window
	Window::size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	// Assign current view to Window::view
	Window::view = this->getDefaultView();
	// Sets the view to the appropriate zoom level for display
	while (Window::view.getSize().x > MAP_WIDTH_PIXELS * 2)
	{
		Window::view.setSize(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
		Window::view.setCenter(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
	}
	this->setView(Window::view);
}

void Window::pollEvents()
{
    sf::Event event;
    while (this->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->close();
            break;
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                this->close();
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void Window::drawText(std::string string)
{
    font.textRect.setPosition(font.startPos);
    // to do. horizontal bounds implementation
    const sf::Vector2f moveR(7.f, 0.f);
    //const sf::Vector2f newLine(font.getPos().x, font.getPos().y + 10);
	for (int i = 0; i < string.length(); i++)
	{
		const char letter = static_cast<char>(string[i]);
        if (font.attachCharTextureToRect(letter))
        {
            if (i != 0)
            {
                font.textRect.move(moveR);
            }
            this->draw(font.textRect);
        }
	}
}