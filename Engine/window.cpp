#pragma once
#include "window.h"

Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	setGameIcon();
	//DEV_TOOLS.toggleFreeMovement(); // For dev mode free-panning view
	// Get the size of the window
	size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	setpixelSize(0.2f); //default 1.2f
	//setVerticalSyncEnabled(true); // must be disabled for DevTools fps counter to work
	setKeyRepeatEnabled(false); // easier to set eg movement states by checking press and release states
	// Assign current view to Window::view
	view = getDefaultView();
	// Sets the view to the appropriate zoom level for display
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
	tileSize = 32;
	uniqueScreenSizeGridSize = pairI(size.x / (tileSize * pixelSize), size.y / (tileSize * pixelSize));
	
	//spriteVector.push_back(arson.sprite);

	//Noise::m_initSimplex(size.x / pixelSize, size.y / pixelSize, 4); Used to be screen size, changed to chunk size.
	Noise::m_initSimplex(32 * TILES_PER_CHUNK_X, 32 * TILES_PER_CHUNK_Y, 4);

}

// Set Icon
void Window::setGameIcon()
{
	/*
	sf::Uint8* pixels = new sf::Uint8[32 * 32 * 4];
	for (size_t i = 0; i < gaiaDownA.size(); i++)
	{
		pixels[i] = gaiaDownA[i];
	}
	setIcon(32, 32, pixels);
	delete[] pixels;
	*/
}

// Polls all events
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
			case sf::Keyboard::W:
				DEV_TOOLS.wallToggle();
				break;
			case sf::Keyboard::T:
				imageHandler.transparencyToggle();
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

// View Functions
void Window::setpixelSize(float factor)
{
	if (size.x < CHUNK_WIDTH_PIXELS * (factor * 1)) { pixelSize = 1; }
	else if (size.x < CHUNK_WIDTH_PIXELS * (factor * 2)) { pixelSize = 2; }
	else if (size.x < CHUNK_WIDTH_PIXELS * (factor * 3)) { pixelSize = 3; }
	else if (size.x < CHUNK_WIDTH_PIXELS * (factor * 4)) { pixelSize = 4; }
	else { pixelSize = 2; }
	// I doubt we need more.
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
sf::Vector2f Window::getViewCoordinates(int dir)
{
	switch (dir)
	{
	case UL:
		return sf::Vector2f(floatify(view.getCenter().x - view.getSize().x / 2), floatify(view.getCenter().y - view.getSize().y / 2));
		break;
	case UR:
		return sf::Vector2f(floatify(view.getCenter().x + view.getSize().x / 2), floatify(view.getCenter().y - view.getSize().y / 2));
		break;
	case DL:
		return sf::Vector2f(floatify(view.getCenter().x - view.getSize().x / 2), floatify(view.getCenter().y + view.getSize().y / 2));
		break;
	case DR:
		return sf::Vector2f(floatify(view.getCenter().x + view.getSize().x / 2), floatify(view.getCenter().y + view.getSize().y / 2));
		break;
	default:
		// UL
		return sf::Vector2f(floatify(view.getCenter().x - view.getSize().x / 2), floatify(view.getCenter().y - view.getSize().y / 2));
		break;
	}
}
void Window::moveViewByCharacter()
{
	const sf::Vector2i pos = pairI(intify(getCharacterByOrder(1).sprite.getPosition().x), intify(getCharacterByOrder(1).sprite.getPosition().y));
	sf::Vector2i oneSixthOfVisibleGrid{ pairI(uniqueScreenSizeGridSize.x / 6, uniqueScreenSizeGridSize.y / 6) };

	// Move view when character is offset from the center by one sixth of the displayed grid size
	if (pos.x > view.getCenter().x + (tileSize * pixelSize) * oneSixthOfVisibleGrid.x)
	{
		if (getViewCoordinates(UR).x < imageHandler.sceneSize.x * pixelSize)
		{
			view.move(getCharacterByOrder(1).movementStepSize * pixelSize, 0);
			this->setView(view);
		}
	}
	else if (pos.x + (tileSize * pixelSize) * oneSixthOfVisibleGrid.x < view.getCenter().x)
	{
		if (getViewCoordinates(UL).x > 0)
		{
			view.move(-getCharacterByOrder(1).movementStepSize * pixelSize, 0);
			this->setView(view);
		}
	}
	if (pos.y > view.getCenter().y + (tileSize * pixelSize) * oneSixthOfVisibleGrid.y)
	{
		if (getViewCoordinates(DL).y < imageHandler.sceneSize.y * pixelSize)
		{
			view.move(0, getCharacterByOrder(1).movementStepSize * pixelSize);
			this->setView(view);
		}
	}
	else if (pos.y + (tileSize * pixelSize) * oneSixthOfVisibleGrid.y < view.getCenter().y)
	{
		if (getViewCoordinates(UL).y > 0)
		{
			view.move(0, -getCharacterByOrder(1).movementStepSize * pixelSize);
			this->setView(view);
		}
	}
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
sf::Vector2i Window::getGridPosition()
{
	return sf::Vector2i(
		getCharacterByOrder(1).sprite.getPosition().x / (tileSize * pixelSize),
		getCharacterByOrder(1).sprite.getPosition().y / (tileSize * pixelSize)
	);
}

// Tilemap Functions
void Window::drawTileMapsBack()
{
	imageHandler.tilemapWindowBack.setScale(sf::Vector2f(pixelSize, pixelSize));
	this->draw(imageHandler.tilemapWindowBack);
}
void Window::drawTileMapsFront()
{
	//const int alpha{(imageHandler.transparency) ? 160 : 255 };
	//imageHandler.tilemapWindowFront.setFillColor(sf::Color(255, 255, 255, alpha)); //neat, global transparency.
	imageHandler.tilemapWindowFront.setScale(sf::Vector2f(pixelSize, pixelSize));

	/*
	sf::CircleShape circle;
	circle.setRadius(32);
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	circle.setPosition(getCharacterByOrder(1).sprite.getPosition());

	//imageHandler.tilemapRenderFront.draw(circle, sf::BlendNone);

	
	imageHandler.tempRender.draw(imageHandler.tilemapWindowFront);
	imageHandler.tempRender.draw(circle, sf::BlendNone);

	imageHandler.tempRender.display();
	imageHandler.tempRectangle.setTexture(&imageHandler.tempRender.getTexture());

	this->draw(imageHandler.tempRectangle);
	imageHandler.tempRender.clear(sf::Color::Transparent);
*/
	this->draw(imageHandler.tilemapWindowFront);

}

// Sprite Functions
void Window::sortSpriteVectorByHeight()
{
	spriteVector.push_back(getCharacterByOrder(4).sprite);
	spriteVector.push_back(getCharacterByOrder(3).sprite);
	spriteVector.push_back(getCharacterByOrder(2).sprite);
	spriteVector.push_back(getCharacterByOrder(1).sprite);
	std::sort(
		spriteVector.begin(),
		spriteVector.end(),
		[](const sf::Sprite& sprite, const sf::Sprite& sprite2)
		{
			return sprite.getPosition().y < sprite2.getPosition().y;
		});
}
void Window::moveCharacters()
{
	// clear previous configuration by clearing stack	
	spriteVector.clear();

	sf::Vector2i pos{
		pairI(intify(getCharacterByOrder(1).sprite.getPosition().x),
			intify(getCharacterByOrder(1).sprite.getPosition().y))
	};

	int x{ 0 };
	int y{ 0 };

	// If the main character is centered on a grid, accept movement input.
	if (pos.x % (tileSize * pixelSize) == 0 && pos.y % (tileSize * pixelSize) == 0)
	{
		if (up && pos.y > 0)
		{
			if (imageHandler.checkBounds(UP, pos / (tileSize * pixelSize)) || DEV_TOOLS.wallToggleBool)
			{
				checkUnderlyingTile(UP);
				getCharacterByOrder(1).sprite.move(0, -getCharacterByOrder(1).movementStepSize * pixelSize);
				changeFalseLastKeyState(lastKeyUp);
				y = -1;
			}
			else
			{
				getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).upBBool);
				getCharacterByOrder(1).animCode = 0;
			}
		}
		else if (up) { getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).upBBool); }
		else if (down && pos.y < intify(imageHandler.sceneSize.y) * pixelSize - (tileSize * pixelSize))
		{
			if (imageHandler.checkBounds(DOWN, pos / (tileSize * pixelSize)) || DEV_TOOLS.wallToggleBool)
			{
				checkUnderlyingTile(DOWN);

				getCharacterByOrder(1).sprite.move(0, getCharacterByOrder(1).movementStepSize * pixelSize);
				changeFalseLastKeyState(lastKeyDown);
				y = 1;
			}
			else
			{
				getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).downBBool);
				getCharacterByOrder(1).animCode = 0;
			}
		}
		else if (down) { getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).downBBool); }
		else if (left && pos.x > 0)
		{
			if (imageHandler.checkBounds(LEFT, pos / (tileSize * pixelSize)) || DEV_TOOLS.wallToggleBool)
			{
				checkUnderlyingTile(LEFT);

				getCharacterByOrder(1).sprite.move(-getCharacterByOrder(1).movementStepSize * pixelSize, 0);
				changeFalseLastKeyState(lastKeyLeft);
				x = -1;
			}
			else
			{
				getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).leftBBool);
				getCharacterByOrder(1).animCode = 0;
			}
		}
		else if (left) { getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).leftBBool); }
		else if (right && pos.x < intify(imageHandler.sceneSize.x) * pixelSize - (tileSize * pixelSize))
		{
			if (imageHandler.checkBounds(RIGHT, pos / (tileSize * pixelSize)) || DEV_TOOLS.wallToggleBool)
			{
				checkUnderlyingTile(RIGHT);

				getCharacterByOrder(1).sprite.move(getCharacterByOrder(1).movementStepSize * pixelSize, 0);
				changeFalseLastKeyState(lastKeyRight);
				x = 1;
			}
			else
			{
				getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).rightBBool);
				getCharacterByOrder(1).animCode = 0;
			}
		}
		else if (right) { getCharacterByOrder(1).textureUpdate(getCharacterByOrder(1).rightBBool); }
	}
	else // auto complete movement until centered on a grid.
	{
		if (pos.x % (tileSize * pixelSize) != 0)
		{
			if (lastKeyRight)
			{
				getCharacterByOrder(1).sprite.move(getCharacterByOrder(1).movementStepSize * pixelSize, 0);
				x = 1;
			}
			else if (lastKeyLeft)
			{
				getCharacterByOrder(1).sprite.move(-getCharacterByOrder(1).movementStepSize * pixelSize, 0);
				x = -1;
			}
		}
		else if (pos.y % (tileSize * pixelSize) != 0)
		{
			if (lastKeyUp)
			{
				getCharacterByOrder(1).sprite.move(0, -getCharacterByOrder(1).movementStepSize * pixelSize);
				y = -1;
			}
			else if (lastKeyDown)
			{
				getCharacterByOrder(1).sprite.move(0, getCharacterByOrder(1).movementStepSize * pixelSize);
				y = 1;
			}
		}
	}
	if (x != 0 || y != 0)
	{
		getCharacterByOrder(1).changeAnimationState(x, y);
		getCharacterByOrder(1).coordVector.push_back(x);
		getCharacterByOrder(1).coordVector.push_back(y);
	}
	getCharacterByOrder(2).follow(getCharacterByOrder(1), pixelSize);
	getCharacterByOrder(3).follow(getCharacterByOrder(2), pixelSize);
	getCharacterByOrder(4).follow(getCharacterByOrder(3), pixelSize);

	getCharacterByOrder(1).checkTimeout();
	getCharacterByOrder(2).checkTimeout();
	getCharacterByOrder(3).checkTimeout();
	getCharacterByOrder(4).checkTimeout();



}
void Window::pollMovement()
{
	moveCharacters();
	sortSpriteVectorByHeight();
	moveViewByCharacter();	
}
Character& Window::getCharacterByOrder(int order)
{
	if (arson.order == order) { return arson; }
	else if (gaia.order == order) { return gaia; }
	else if (cole.order == order) { return cole; }
	else if (neko.order == order) { return neko; }
	else { return arson; }
}
void Window::checkUnderlyingTile(int dir)
{
	// For each character...
	for (int i = 1; i <= 4; i++)
	{
		if (i == 4 && 
			getCharacterByOrder(1).spriteColour == SpriteColor::Default &&
			getCharacterByOrder(2).spriteColour == SpriteColor::Default &&
			getCharacterByOrder(3).spriteColour == SpriteColor::Default &&
			getCharacterByOrder(4).spriteColour == SpriteColor::Default
			)
		{
			getCharacterByOrder(1).movementStepSize = 4;
			while (getCharacterByOrder(1).coordVector.size() > 128 / (4 * pixelSize))
			{
				getCharacterByOrder(1).coordVector.pop_back();
			}
			getCharacterByOrder(2).movementStepSize = 4;
			while (getCharacterByOrder(2).coordVector.size() > 128 / (4 * pixelSize))
			{
				getCharacterByOrder(2).coordVector.pop_back();
			}
			getCharacterByOrder(3).movementStepSize = 4;
			while (getCharacterByOrder(3).coordVector.size() > 128 / (4 * pixelSize))
			{
				getCharacterByOrder(3).coordVector.pop_back();
			}
			getCharacterByOrder(4).movementStepSize = 4;
			while (getCharacterByOrder(4).coordVector.size() > 128 / (4 * pixelSize))
			{
				getCharacterByOrder(4).coordVector.pop_back();
			}
		}

		// Get Grid Position for each character
		int xx{ intify(getCharacterByOrder(i).sprite.getPosition().x / (tileSize * pixelSize)) };
		int yy{ intify(getCharacterByOrder(i).sprite.getPosition().y / (tileSize * pixelSize)) };

		// If character is not in the lead, check lead coordinates and adjust direction
		if (i > 1)
		{
			if (getCharacterByOrder(i - 1).coordVector[1] == -1)
			{
				dir = UP;
			}
			else if (getCharacterByOrder(i - 1).coordVector[1] == 1)
			{
				dir = DOWN;
			}
			else if (getCharacterByOrder(i - 1).coordVector[0] == -1)
			{
				dir = LEFT;
			}
			else if (getCharacterByOrder(i - 1).coordVector[0] == 1)
			{
				dir = RIGHT;
			}
		}

		// If the tile in the direction of travel will be under the character...
		switch (dir)
		{
		case UP:
			if (water.westKagarWater[(TILES_PER_CHUNK_X * 4) * (yy - 1) + xx]) 
			{ 
				getCharacterByOrder(i).spriteColour = SpriteColor::Blue; 
				if (i == 1) { getCharacterByOrder(i).movementStepSize = 1; }
				else { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			else
			{ 
				getCharacterByOrder(i).spriteColour = SpriteColor::Default;
				if (i != 1 && getCharacterByOrder(i - 1).spriteColour == SpriteColor::Default) { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			break;
		case DOWN:
			if (water.westKagarWater[(TILES_PER_CHUNK_X * 4) * (yy + 1) + xx]) 
			{ 
				getCharacterByOrder(i).spriteColour = SpriteColor::Blue;
				if (i == 1) { getCharacterByOrder(i).movementStepSize = 1; }
				else { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			else
			{
				getCharacterByOrder(i).spriteColour = SpriteColor::Default;
				if (i != 1 && getCharacterByOrder(i - 1).spriteColour == SpriteColor::Default) { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			break;
		case LEFT:
			if (water.westKagarWater[(TILES_PER_CHUNK_X * 4) * yy + xx - 1]) 
			{ 
				getCharacterByOrder(i).spriteColour = SpriteColor::Blue;
				if (i == 1) { getCharacterByOrder(i).movementStepSize = 1; }
				else { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			else
			{
				getCharacterByOrder(i).spriteColour = SpriteColor::Default;
				if (i != 1 && getCharacterByOrder(i - 1).spriteColour == SpriteColor::Default) { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			break;
		case RIGHT:
			if (water.westKagarWater[(TILES_PER_CHUNK_X * 4) * yy + xx + 1]) 
			{ 
				getCharacterByOrder(i).spriteColour = SpriteColor::Blue;
				if (i == 1) { getCharacterByOrder(i).movementStepSize = 1; }
				else { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			else
			{
				getCharacterByOrder(i).spriteColour = SpriteColor::Default;
				if (i != 1 && getCharacterByOrder(i - 1).spriteColour == SpriteColor::Default) { getCharacterByOrder(i).movementStepSize = getCharacterByOrder(i - 1).movementStepSize; }
			}
			break;
		default:
			break;
		}
	}
}
void Window::drawSprites()
{
	for (size_t i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i].setPosition(pairF(spriteVector[i].getPosition().x, spriteVector[i].getPosition().y - (8 * pixelSize)));
		spriteVector[i].setScale(pixelSize, pixelSize);
		this->draw(spriteVector[i]);
	}
}

// Particle Functions
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
	drawParticles();
}

// Noise Functions
void Window::setPositionAndDraw(float x, float y)
{
	sf::Vector2f noiseOrigin = pairF(x, y);

	// Row 0
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 0), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y + (noise.getSize().y * pixelSize * -1)));
	this->draw(noise);

	// Row 1
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y));
	this->draw(noise);
	// Drawn in previous function
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y));
	this->draw(noise);

	// Row 2
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 0), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y + (noise.getSize().y * pixelSize * 1)));
	this->draw(noise);

	// Row 3
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 0), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y + (noise.getSize().y * pixelSize * 2)));
	this->draw(noise);

	// Row 4
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 0), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y + (noise.getSize().y * pixelSize * 3)));
	this->draw(noise);

	// Row 5
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * -1), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 0), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 1), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 2), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 3), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
	noise.setPosition(sf::Vector2f(x + (noise.getSize().x * pixelSize * 4), y + (noise.getSize().y * pixelSize * 4)));
	this->draw(noise);
}
void Window::m_groupDraw(sf::Vector2f direction)
{
	noise.move(direction);
	sf::Vector2f noiseOrigin = noise.getPosition();

	if (noise.getPosition().x < noise.getSize().x * -pixelSize)
	{
		noise.setPosition(direction.x, noise.getPosition().y);
		noiseOrigin = noise.getPosition();
	}
	if (noise.getPosition().y < noise.getSize().y * -pixelSize)
	{
		noise.setPosition(noise.getPosition().x, direction.y);
		noiseOrigin = noise.getPosition();
	}
	this->draw(noise);
	setPositionAndDraw(noiseOrigin.x, noiseOrigin.y);
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
	noise.setScale(sf::Vector2f(pixelSize, pixelSize));
	simplexSpeed++;
	if (simplexSpeed > delay)
	{
		simplexSpeed = 0;
		simplexMovementCollector.x = simplexMovementCollector.x + direction.x;
		simplexMovementCollector.y = simplexMovementCollector.y + direction.y;
		if ((simplexMovementCollector.x >= pixelSize) && (simplexMovementCollector.y >= pixelSize))
		{
			simplexMovementCollector.x = 0.f;
			simplexMovementCollector.y = 0.f;
			m_groupDraw(sf::Vector2f(pixelSize, pixelSize));
		}
		else if (simplexMovementCollector.x >= pixelSize)
		{
			simplexMovementCollector.x = 0.f;
			m_groupDraw(sf::Vector2f(pixelSize, 0));
		}
		else if (simplexMovementCollector.y >= pixelSize)
		{
			simplexMovementCollector.y = 0.f;
			m_groupDraw(sf::Vector2f(0, pixelSize));
		}
		else if ((simplexMovementCollector.x <= -pixelSize) && (simplexMovementCollector.y <= -pixelSize))
		{
			simplexMovementCollector.x = 0.f;
			simplexMovementCollector.y = 0.f;
			m_groupDraw(sf::Vector2f(-pixelSize, -pixelSize));
		}
		else if (simplexMovementCollector.x <= -pixelSize)
		{
			simplexMovementCollector.x = 0.f;
			m_groupDraw(sf::Vector2f(-pixelSize, 0));
		}
		else if (simplexMovementCollector.y <= -pixelSize)
		{
			simplexMovementCollector.y = 0.f;
			m_groupDraw(sf::Vector2f(0, -pixelSize));
		}
		else
		{
			m_groupDraw();
		}
	}
	else if (simplexSpeed != 0)
	{
		m_groupDraw();
	}
}

// Flow Functions
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

// Water Functions
void Window::drawWaterTile()
{
	// Is automatic, prints on tiles 89 and 90.
	water.update(water.clock.getElapsedTime());

	if (!water.westKagarWater.size())
	{
		for (size_t i = 0; i < imageHandler.tileMapE.masterTile.size(); i++)
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

	for (int i = 0; i < TILES_PER_CHUNK_X * 4; i++)
	{
		for (int j = 0; j < TILES_PER_CHUNK_Y * 4; j++)
		{
			if (water.westKagarWater[i + j * (TILES_PER_CHUNK_X * 4)])
			{
				water.noise.setScale(pixelSize, pixelSize);
				water.noise.setPosition(water.width * pixelSize * i, water.height * pixelSize * j);
				draw(water.noise);
			}
		}
	}
	 
	//reset
	water.noise.setPosition(0, 0);
}

// Text Functions
void Window::drawDevToolsText()
{
	drawText("FPS: " + this->DEV_TOOLS.getFPS(), getViewCoordinates(UR), 2); // 1100 - 1200 fps
	drawText
	(
		"X: " + std::to_string(intify(getGridPosition().x)) +
		", Y :" + std::to_string(intify(getGridPosition().y)),
		getViewCoordinates(DR),
		2
	);
	drawText("Location: West Kagar", getViewCoordinates(DL), 2);
	if (this->DEV_TOOLS.wallToggleBool) { drawText("NO WALLS", getViewCoordinates(UL), 2); }
}
void Window::drawText(std::string string, sf::Vector2f startPosition, int scale)
{
	scale += 1;
	const int fontScale{ (scale < 2) ? 2 : scale };
	font.setStartPos(sf::Vector2f(startPosition.x + 1, startPosition.y + 1));
	font.setPos(font.getStartPos());

	// GET CHARACTER COUNTS FOR EACH TYPE OF CHARACTER.
	int specialCount{ 0 };
	int punctuationCount{ 0 };
	for (size_t i = 0; i < string.length(); i++)
	{
		if (string[i] == '^' ||
			string[i] == '|' ||
			string[i] == '<' ||
			string[i] == '{' ||
			string[i] == '=' ||
			string[i] == '_')
		{ specialCount++; }
		else if (
			string[i] == ',' ||
			string[i] == '.' ||
			string[i] == ':')
		{ punctuationCount++; }
	}
	int normalCount{ intify(string.length()) - specialCount - punctuationCount };
	int messageWidth{ (9 * specialCount * fontScale) + (3 * punctuationCount * fontScale) + (7 * normalCount * fontScale) };

	// Bounds Right
	if ((intify(startPosition.x) + messageWidth) > intify(getViewCoordinates(UR).x))
	{
		startPosition.x = floatify(getViewCoordinates(UR).x - messageWidth);
		font.setStartPos(startPosition);
		font.setPos(startPosition);
	}
	// Bounds Left
	if (intify(startPosition.x) <= getViewCoordinates(UL).x)
	{
		startPosition.x = floatify(getViewCoordinates(UL).x + (fontScale * 2));
		font.setStartPos(startPosition);
		font.setPos(startPosition);
	}
	// Bounds Bottom
	if (intify(startPosition.y) + 8 > intify(getViewCoordinates(DR).y))
	{
		startPosition.y = floatify(getViewCoordinates(DR).y - (8 * fontScale) - fontScale);
		font.setStartPos(startPosition);
		font.setPos(startPosition);
	}
	// Bounds Top
	if (intify(startPosition.y) <= getViewCoordinates(UL).y)
	{
		startPosition.y = floatify(getViewCoordinates(UL).y + (fontScale * 2));
		font.setStartPos(startPosition);
		font.setPos(startPosition);
	}

	// prints characters.
	for (int i = 0; i <= 1; i++)
	{
		// Runs twice to set a shadow effect
		if (i == 0)
		{
			font.setColor(sf::Color(0, 0, 0), true);
		}
		else
		{
			font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue));
			font.setPos(sf::Vector2f(font.getPos().x - fontScale, font.getPos().y - fontScale));
		}
		for (size_t j = 0; j < string.length(); j++)
		{
			const char letter = string[j];
			if (font.attachCharImageSubRectToSprite(letter))
			{
				if (j != 0)
				{
					font.setPos(sf::Vector2f(font.getPos().x + (font.addon.x + font.moveR.x) * fontScale, font.getPos().y + (font.addon.y + font.moveR.y) * fontScale));
					if (letter == '^' ||
						letter == '|' ||
						letter == '<' ||
						letter == '{' ||
						letter == '_' ||
						letter == '=')
					{
						font.moveR = sf::Vector2f(9.f, 0.f);
					}
					else if (letter == ',' ||
						letter == '.' ||
						letter == ':')
					{
						font.moveR = sf::Vector2f(3.f, 0.f);
					}
					else
					{
						font.moveR = sf::Vector2f(7.f, 0.f);
					}
				}
				font.charSprite.setScale(sf::Vector2f(fontScale, fontScale));
				this->draw(font.charSprite);
				if (font.addon.y > 0) { font.setPos(sf::Vector2f(font.getPos().x, font.getPos().y - floatify(font.addon.y * fontScale))); font.addon.y = 0; }
				//if (font.addon.x < 0) { font.move(sf::Vector2f(font.addon.x * fontScale, 0)); font.addon.x = 0; }
				//if (letter == 'l' || letter == 'i') { font.move(sf::Vector2f(-fontScale, 0)); }
			}
			else
			{
				std::cout << "couldn't attach char image";
			}
		}
		font.setPos(font.getStartPos());
	} 
}
