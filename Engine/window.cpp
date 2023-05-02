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

template <typename T>
void Window::drawText(T const& value, sf::Vector2f startPosition)
{
    std::string string{ static_cast<std::string>(value) };
    // Sets character kerning
    const sf::Vector2f moveR(7.f, 0.f);
    font.setStartPos(startPosition);

    for (int i = 0; i <= 1; i++)
    {
        // Sets initial position to startPos value
        // Creates shadow effect through duplication
        if (i == 0)
        {
            font.setColor(0, 0, 0);
            font.setPos(sf::Vector2f(font.getPos().x + 0.5, font.getPos().y + 0.5));
        }
        else
        {
            font.setColor(255, 255, 255);
            font.setPos(sf::Vector2f(font.getPos().x - 0.5, font.getPos().y - 0.5));
        }

        // prints characters. runs twice for shadow effect
        for (int j = 0; j < string.length(); j++)
        {
            const char letter = static_cast<char>(string[j]);
            if (font.attachCharTextureToRect(letter))
            {
                if (j != 0)
                {
                    font.move(moveR);
                }

                this->draw(font.getRect());
            }
        }
        font.setPos(font.getStartPos());
    }
}