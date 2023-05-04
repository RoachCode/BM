#pragma once
#include "window.h"
#include <iostream>

// Call constructor, which calls inherited constructor from sf::RenderWindow
Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	// Get the size of the window
	Window::size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	this->setVerticalSyncEnabled(true); // must be disabled for DevTools fps counter to work
	this->setKeyRepeatEnabled(false); // easier to set eg movement states by checking press and release states
	// Assign current view to Window::view
	Window::view = this->getDefaultView();
	// Sets the view to the appropriate zoom level for display
	while (Window::view.getSize().x > MAP_WIDTH_PIXELS * 2)
	{
		Window::view.setSize(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
		Window::view.setCenter(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
	}
	this->setView(Window::view);
	isMovingView = false;
}

void Window::pollEvents()
{
	pollMovement();
    sf::Event event;
    while (this->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->close();
            break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Down:
				startViewMovement(sf::Vector2f(0, 4));
				break;
			case sf::Keyboard::Right:
				startViewMovement(sf::Vector2f(4, 0));
				break;
			case sf::Keyboard::Left:
				startViewMovement(sf::Vector2f(-4, 0));
				break;
			case sf::Keyboard::Up:
				startViewMovement(sf::Vector2f(0, -4));
				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				this->close();
				break;
			case sf::Keyboard::Numpad1:
				DEV_TOOLS.zDepth = 1;
				break;
			case sf::Keyboard::Numpad2:
				DEV_TOOLS.zDepth = 2;
				break;
			case sf::Keyboard::Numpad3:
				DEV_TOOLS.zDepth = 3;
				break;
			case sf::Keyboard::Numpad4:
				DEV_TOOLS.zDepth = 4;
				break;
			case sf::Keyboard::Numpad5:
				DEV_TOOLS.zDepth = 5;
				break;
			case sf::Keyboard::Numpad6:
				DEV_TOOLS.zDepth = 6;
				break;
			case sf::Keyboard::Numpad7:
				DEV_TOOLS.zDepth = 7;
				break;
			case sf::Keyboard::Numpad8:
				DEV_TOOLS.zDepth = 8;
				break;
			case sf::Keyboard::Numpad9:
				DEV_TOOLS.zDepth = 9;
				break;
			case sf::Keyboard::Numpad0:
				DEV_TOOLS.zDepth = 10;
				break;
			case sf::Keyboard::Down:
				if (isMovingView) { endViewMovement(); }
				break;
			case sf::Keyboard::Right:
				if (isMovingView) { endViewMovement(); }
				break;
			case sf::Keyboard::Left:
				if (isMovingView) { endViewMovement(); }
				break;
			case sf::Keyboard::Up:
				if (isMovingView) { endViewMovement(); }
				break;
			default:
				break;
			}
			break;
        default:
            break;
        }
    }
}

int Window::getZoomFactor()
{
	return static_cast<int>(size.x / view.getSize().x);
}

void Window::drawText(std::string string, sf::Vector2f startPosition)
{
	font.setStartPos(startPosition);
	int pixelWidth{ static_cast<int>(font.moveR.x) * static_cast<int>(string.length()) };

	if (static_cast<int>(startPosition.x) + pixelWidth > static_cast<int>(size.x))
	{
		font.setStartPos(sf::Vector2f(size.x / getZoomFactor() - pixelWidth, startPosition.y));
	}
	// Runs twice to set a shadow effect
	for (int i = 0; i <= 1; i++)
	{
		// Creates shadow effect through duplication
		if (i == 0)
		{
			font.setColor(sf::Color(0, 0, 0), true);
			font.setPos(sf::Vector2f(font.getPos().x + 0.5, font.getPos().y + 0.5));
		}
		else
		{
			// why in the fuck can I only set my text color here?
			//font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue, 255));
			font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue), true);
			font.setPos(sf::Vector2f(font.getPos().x - 0.5, font.getPos().y - 0.5));
		}

		// prints characters.
		for (int j = 0; j < string.length(); j++)
		{
			const char letter = string[j];
			if (font.attachCharImageSubRectToSprite(letter))
			{
				if (j != 0)
				{
					font.move(font.moveR);
				}

				this->draw(font.charSprite);
			}
		}
		font.setPos(font.getStartPos());
	}
}

void Window::drawTileMaps()
{
	//todo: find a way to draw all the layers consecutively onto a single image, for a single draw.
	for (int i = 0; i < DEV_TOOLS.zDepth; i++)
	{
		this->draw(*imageHandler.tilemapVector[i]);
	}
}

void Window::startViewMovement(sf::Vector2f offset)
{
	if (DEV_TOOLS.freeMovementAllowed)
	{
		isMovingView = true;
		movementOffset = offset;
	}
}

void Window::endViewMovement()
{
	isMovingView = false;
}

void Window::pollMovement()
{
	if (isMovingView)
	{
		view.move(movementOffset.x, movementOffset.y);
		this->setView(view);
	}
}

void Window::drawSprites()
{
	//
}