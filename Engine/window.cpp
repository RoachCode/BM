#pragma once
#include "window.h"

Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	//DEV_TOOLS.toggleFreeMovement(); // For dev mode free-panning view
	// Get the size of the window
	size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	//setVerticalSyncEnabled(true); // must be disabled for DevTools fps counter to work
	setKeyRepeatEnabled(false); // easier to set eg movement states by checking press and release states
	// Assign current view to Window::view
	view = getDefaultView();
	// Sets the view to the appropriate zoom level for display
	windowScale = 1;
	while (size.x > (CHUNK_WIDTH_PIXELS * windowScale * 2))
	{
		windowScale *= 2;
	}
	windowScale = 2; //temp
	setView(view);
	movementAllowed = false;
	lastKeyUp = false;
	lastKeyDown = false;
	lastKeyLeft = false;
	lastKeyRight = false;
	up = false;
	down = false;
	left = false;
	right = false;
	movementStepSize = 4 * windowScale;
	tileSize = 32 * windowScale;
	uniqueScreenSizeGridSize = pairI(size.x / tileSize, size.y / tileSize);
	
	spriteVector.push_back(arson.sprite);

	Noise::m_initSimplex(size.x / windowScale, size.y / windowScale, 4);

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
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Down:
				down = true;
				break;
			case sf::Keyboard::Right:
				right = true;
				break;
			case sf::Keyboard::Left:
				left = true;
				break;
			case sf::Keyboard::Up:
				up = true;
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
				imageHandler.zDepth = 1;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad2:
				imageHandler.zDepth = 2;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad3:
				imageHandler.zDepth = 3;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad4:
				imageHandler.zDepth = 4;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad5:
				imageHandler.zDepth = 5;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad6:
				imageHandler.zDepth = 6;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad7:
				imageHandler.zDepth = 7;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad8:
				imageHandler.zDepth = 8;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad9:
				imageHandler.zDepth = 9;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Numpad0:
				imageHandler.zDepth = 10;
				imageHandler.loadWestKagar();
				break;
			case sf::Keyboard::Up:
				up = false;
				break;
			case sf::Keyboard::Down:
				down = false;
				break;
			case sf::Keyboard::Left:
				left = false;
				break;
			case sf::Keyboard::Right:
				right = false;
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.key.code)
			{
			case sf::Mouse::Left:
				particles.particleBool = true;
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			particles.particleBool = false;
			break;
        default:
            break;
        }
    }
	pollMovement();

}

void Window::drawText(std::string string, sf::Vector2f startPosition)
{
	font.setStartPos(startPosition);
	font.setPos(font.getStartPos());
	int pixelWidth{ static_cast<int>(font.moveR.x) * static_cast<int>(string.length()) * windowScale };
	// bounds on the right. so far only right side.
	if ((static_cast<int>(startPosition.x) + pixelWidth) > static_cast<int>(size.x) * windowScale)
	{
		// - 1 is so the shadow offset is also kept in bounds
		font.setStartPos(sf::Vector2f(size.x - pixelWidth - 1, startPosition.y));
		font.setPos(font.getStartPos());
	}

	// Runs twice to set a shadow effect
	for (int i = 0; i <= 1; i++)
	{
		// Creates shadow effect through duplication
		if (i == 0)
		{
			font.setColor(sf::Color(0, 0, 0), true);
			font.setPos(sf::Vector2f(font.getPos().x + 1, font.getPos().y + 1));
		}
		else
		{
			// why in the fuck can I only set my text color here?
			//font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue, 255));
			font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue), true);
			font.setPos(sf::Vector2f(font.getPos().x - 1, font.getPos().y - 1));
		}

		// prints characters.
		for (int j = 0; j < string.length(); j++)
		{
			const char letter = string[j];
			if (font.attachCharImageSubRectToSprite(letter))
			{
				if (j != 0)
				{
					font.move(sf::Vector2f(font.moveR.x * windowScale, font.moveR.y * windowScale));
				}
				font.charSprite.setScale(sf::Vector2f(windowScale, windowScale));
				this->draw(font.charSprite);
			}
			else
			{
				std::cout << "couldn't attach char image";
			}
		}
		font.setPos(font.getStartPos());
	}
}

void Window::drawTileMapsBack()
{
	imageHandler.tilemapWindowBack.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(imageHandler.tilemapWindowBack);
}

void Window::drawTileMapsFront()
{
	imageHandler.tilemapWindowFront.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(imageHandler.tilemapWindowFront);
}

void Window::startViewMovement(sf::Vector2f offset)
{
	if (DEV_TOOLS.queryFreeMovement())
	{
		movementAllowed = true;
		movementOffset = offset;
	}
}

void Window::endViewMovement()
{
	movementAllowed = false;
	movementOffset = sf::Vector2f(0.f, 0.f);
}

void Window::refreshMovementBools()
{
	lastKeyUp = false;
	lastKeyDown = false;
	lastKeyLeft = false;
	lastKeyRight = false;
}
void Window::changeFalseLastKeyState(bool& lastKeyInput)
{
	if (!lastKeyInput)
	{
		refreshMovementBools();
		lastKeyInput = true;
	}
}
sf::Vector2i Window::getTopLeftViewCoordinates()
{
	return sf::Vector2i(view.getCenter().x - (size.x / windowScale), view.getCenter().y - (size.y / windowScale));
}
void Window::pollMovement()
{
	sf::Vector2i pos{ pairI(intify(spriteVector[0].getPosition().x), intify(spriteVector[0].getPosition().y)) };
	sf::Vector2i oneSixthOfVisibleGrid{ pairI(uniqueScreenSizeGridSize.x / 6, uniqueScreenSizeGridSize.y / 6) };
	
	// clear previous configuration by clearing stack	
	spriteVector.clear();
	
	int x{ 0 };
	int y{ 0 };

	// If the character is centered on a grid, accept movement input.
	if (pos.x % tileSize == 0 && pos.y % tileSize == 0)
	{
		if (up && pos.y > 0 && imageHandler.checkBounds(UP, pos / tileSize))
		{
			arson.sprite.move(0, -movementStepSize);
			changeFalseLastKeyState(lastKeyUp);
			y = -1;
		}
		else if (down && pos.y < imageHandler.sceneSize.y * windowScale - tileSize && imageHandler.checkBounds(DOWN, pos / tileSize))
		{
			arson.sprite.move(0, movementStepSize);
			changeFalseLastKeyState(lastKeyDown);
			y = 1;
		}
		else if (left && pos.x > 0 && imageHandler.checkBounds(LEFT, pos / tileSize))
		{
			arson.sprite.move(-movementStepSize, 0);
			changeFalseLastKeyState(lastKeyLeft);
			x = -1;
		}
		else if (right && pos.x < imageHandler.sceneSize.x * windowScale - tileSize && imageHandler.checkBounds(RIGHT, pos / tileSize))
		{
			arson.sprite.move(movementStepSize, 0);
			changeFalseLastKeyState(lastKeyRight);
			x = 1;
		}
	}
	else // auto complete movement until centered on a grid.
	{
		if (pos.x % tileSize != 0)
		{
			if (lastKeyRight)
			{
				arson.sprite.move(movementStepSize, 0);
				x = 1;
			}
			else if (lastKeyLeft)
			{
				arson.sprite.move(-movementStepSize, 0);
				x = -1;
			}
		}
		else if (pos.y % tileSize != 0)
		{
			if (lastKeyUp)
			{
				arson.sprite.move(0, -movementStepSize);
				y = -1;
			}
			else if (lastKeyDown)
			{
				arson.sprite.move(0, movementStepSize);
				y = 1;
			}
		}
	}

	arson.changeAnimationState(x, y);

	// Move view when character is offset from the center by one sixth of the displayed grid size
	if (pos.x > view.getCenter().x + tileSize * oneSixthOfVisibleGrid.x)
	{
		if (getTopLeftViewCoordinates().x + size.x < imageHandler.sceneSize.x * windowScale) //
		{
			view.move(movementStepSize, 0);
			this->setView(view);
		}
	}
	else if (pos.x + tileSize * oneSixthOfVisibleGrid.x < view.getCenter().x)
	{
		if (getTopLeftViewCoordinates().x > 0)
		{
			view.move(-movementStepSize, 0);
			this->setView(view);
		}
	}
	if (pos.y > view.getCenter().y + tileSize * oneSixthOfVisibleGrid.y)
	{
		if (getTopLeftViewCoordinates().y + size.y < imageHandler.sceneSize.y * windowScale)
		{
			view.move(0, movementStepSize);
			this->setView(view);
		}
	}
	else if (pos.y + tileSize * oneSixthOfVisibleGrid.y < view.getCenter().y)
	{
		if (getTopLeftViewCoordinates().y > 0)
		{
			view.move(0, -movementStepSize);
			this->setView(view);
		}
	}

	// Add back sprite to stack
	spriteVector.push_back(arson.sprite);
}

void Window::drawSprites()
{
	//sprite.spriteVector[0].move(0, (-8 * windowScale)); // Move characters up
	for (auto i : spriteVector)
	{
		this->draw(i);
	}
	//sprite.spriteVector[0].move(0, (8 * windowScale)); // Move characters down

}

void Window::drawParticles()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*this);
	particles.setEmitter(this->mapPixelToCoords(mouse));
	sf::Time elapsed = particles.clock.restart();
	particles.update(elapsed);
	draw(particles);

}
void Window::drawParticles(sf::Color color)
{
	particles.setColor(color);
	//sf::Vector2i mouse = sf::Mouse::getPosition(*this);
	//particles.setEmitter(this->mapPixelToCoords(mouse));
	//sf::Time elapsed = particles.clock.restart();
	//particles.update(elapsed);
	//draw(particles);
	drawParticles();

}

void Window::m_groupDraw(sf::Vector2f direction)
{
	noise.move(direction);
	sf::Vector2f noiseOrigin = noise.getPosition();

	if (noise.getPosition().x < noise.getSize().x * -windowScale)
	{
		noise.setPosition(direction.x, noise.getPosition().y);
		noiseOrigin = noise.getPosition();
	}
	if (noise.getPosition().y < noise.getSize().y * -windowScale)
	{
		noise.setPosition(noise.getPosition().x, direction.y);
		noiseOrigin = noise.getPosition();
	}
	this->draw(noise);

	noise.setPosition(sf::Vector2f(noise.getPosition().x + noise.getSize().x * windowScale, noiseOrigin.y));
	this->draw(noise);

	noise.setPosition(sf::Vector2f(noiseOrigin.x, noise.getPosition().y + noise.getSize().y * windowScale));
	this->draw(noise);

	noise.setPosition(sf::Vector2f(noise.getPosition().x + noise.getSize().x * windowScale, noiseOrigin.y + noise.getSize().y * windowScale));
	this->draw(noise);

	noise.setPosition(noiseOrigin);
}
void Window::m_groupDraw(int dirX, int dirY)
{
	const sf::Vector2f direction = sf::Vector2f(dirX, dirY);
	m_groupDraw(direction);
}
void Window::m_groupDraw()
{
	const sf::Vector2f direction = sf::Vector2f(0, 0);
	m_groupDraw(direction);
}
void Window::drawFullSimplex(sf::Vector2f direction, int delay)
{

	noise.setScale(sf::Vector2f(windowScale, windowScale));
	simplexSpeed++;
	if (simplexSpeed > delay)
	{
		simplexSpeed = 0;
		m_groupDraw(direction);
	}
	else if (simplexSpeed != 0)
	{
		m_groupDraw();
	}
}

bool justOnce{ true };
void Window::drawFlow(FlowPreset& fp)
{
	flow.drawFlow(fp);

	// screenshot
	if (onlyOnceHack)
	{

		std::string filename = flow.currentName + ".png";
		if (!flow.flowWindowTexture.getTexture().copyToImage().saveToFile(filename))
		{
			std::cout << "screenshot failed";
		}
		onlyOnceHack = false;
	}

	this->draw(flow.flowWindow);
	
}
void Window::drawFlow()
{
	if (justOnce)
	{
		flow.drawFlow();
		justOnce = false;
	}
	this->draw(flow.flowWindow);
}

void Window::drawWaterTile()
{
	water.update(water.clock.getElapsedTime());

	if (!water.westKagarWater.size())
	{
		for (int i = 0; i < imageHandler.tileMapE.masterTile.size(); i++)
		{
			if (imageHandler.tileMapE.masterTile[i] == 89 || imageHandler.tileMapE.masterTile[i] == 90)
			{
				water.westKagarWater.push_back(1);
			}
			else
			{
				water.westKagarWater.push_back(0);
			}
		}
	}

	for (int i = 0; i < 24 * 4; i++)
	{
		for (int j = 0; j < 14 * 4; j++)
		{
			if (water.westKagarWater[i + j * (24 * 4)])
			{
				water.noise.setScale(windowScale, windowScale);
				water.noise.setPosition(water.width * windowScale * i, water.height * windowScale * j);
				draw(water.noise);
			}
		}
	}
	 
	//reset
	water.noise.setPosition(0, 0);
}