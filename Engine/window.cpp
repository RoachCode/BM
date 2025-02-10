#pragma once
#include "window.h"

Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Fool's Errand", sf::Style::Fullscreen)
{
	setGameIcon();
	//DEV_TOOLS.toggleFreeMovement(); // For dev mode free-panning view (not implemented yet)
	setView(View::getView());
	setKeyRepeatEnabled(false); // easier to set eg movement states by checking press and release states
	refreshMovementBools();
	up = false;
	down = false;
	left = false;
	right = false;
	
	Noise::m_initSimplex(TILE_SIZE * TILES_PER_CHUNK_X, TILE_SIZE * TILES_PER_CHUNK_Y, 4);
	importantTextBox.box.setAlpha(sf::Uint8(255));
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

// Polls all events, keyboard
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
			case sf::Keyboard::Space:
				menu.toggleMenu();
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
			case sf::Mouse::Middle:
				View::resetZoom();
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			particles.particleBool = false;
			break;
		case sf::Event::MouseWheelScrolled:
			// the delta is an integer
		{
			float delta{ event.mouseWheelScroll.delta / 10 };
			View::zoom(delta);
			break;
		}
        default:
            break;
        }
    }
	// if the menu is closed, poll movement
	if (!menu.menuEnabled()) { pollMovement(); }
}

// Tilemap Functions
void Window::drawTileMapsBack() { this->draw(imageHandler.tilemapWindowBack); }
void Window::drawTileMapsFront() { this->draw(imageHandler.tilemapWindowFront); }

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
	// get values from View class
	int tilePixels{ getTilePixels() };
	int pixelSize{ getPixelSize() };
	sf::Vector2u sceneSize{ getSceneSize() };

	// clear previous configuration by clearing stack	
	spriteVector.clear();

	sf::Vector2i pos{
		pairI(intify(getCharacterByOrder(1).sprite.getPosition().x),
			intify(getCharacterByOrder(1).sprite.getPosition().y))
	};

	int x{ 0 };
	int y{ 0 };

	// If the main character is centered on a grid, accept movement input.
	if (pos.x % (tilePixels) == 0 && pos.y % (tilePixels) == 0)
	{
		if (up && pos.y > 0)
		{
			if (imageHandler.checkBounds(UP, pos / intify(tilePixels)) || DEV_TOOLS.wallToggleBool)
			{
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
		else if (down && pos.y < intify(sceneSize.y) * pixelSize - (tilePixels))
		{
			if (imageHandler.checkBounds(DOWN, pos / intify(tilePixels)) || DEV_TOOLS.wallToggleBool)
			{
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
			if (imageHandler.checkBounds(LEFT, pos / intify(tilePixels)) || DEV_TOOLS.wallToggleBool)
			{
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
		else if (right && pos.x < intify(sceneSize.x) * pixelSize - (tilePixels))
		{
			if (imageHandler.checkBounds(RIGHT, pos / intify(tilePixels)) || DEV_TOOLS.wallToggleBool)
			{
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
		if (pos.x % (tilePixels) != 0)
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
		else if (pos.y % (tilePixels) != 0)
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
		getCharacterByOrder(1).changeAnimationState(x, y, pixelSize);

		//getCharacterByOrder(1).coordVector.clear();

		getCharacterByOrder(1).coordVector.push_back(x);
		getCharacterByOrder(1).coordVector.push_back(y);

		getCharacterByOrder(2).follow(getCharacterByOrder(1), pixelSize);
		getCharacterByOrder(3).follow(getCharacterByOrder(2), pixelSize);
		getCharacterByOrder(4).follow(getCharacterByOrder(3), pixelSize);
		
		checkUnderlyingTile();
	}

	getCharacterByOrder(1).checkTimeout();
	getCharacterByOrder(2).checkTimeout();
	getCharacterByOrder(3).checkTimeout();
	getCharacterByOrder(4).checkTimeout();

}
sf::Vector2i Window::getGridPosition()
{
	return sf::Vector2i(
		getCharacterByOrder(1).sprite.getPosition().x / (getTilePixels()),
		getCharacterByOrder(1).sprite.getPosition().y / (getTilePixels())
	);
}
void Window::pollMovement()
{
	moveCharacters();
	sortSpriteVectorByHeight();
	// bottleneck ahead, fix it.
	this->setView(View::moveViewByCharacter(pairI(intify(getCharacterByOrder(1).sprite.getPosition().x), intify(getCharacterByOrder(1).sprite.getPosition().y)), getCharacterByOrder(1).movementStepSize));
}
Character& Window::getCharacterByOrder(int order)
{
	if (arson.order == order) { return arson; }
	else if (gaia.order == order) { return gaia; }
	else if (cole.order == order) { return cole; }
	else if (neko.order == order) { return neko; }
	else { return arson; }
}
void Window::checkUnderlyingTile()
{
	for (int i = 1; i < 5; i++)
	{
		// Get Grid Position for each character
		int x{ intify(getCharacterByOrder(i).sprite.getPosition().x / (getTilePixels())) };
		int y{ intify(getCharacterByOrder(i).sprite.getPosition().y / (getTilePixels())) };
		int arrayPos{ intify((TILES_PER_CHUNK_X * 4) * y + x) };

		if (water.westKagarWater[arrayPos])
		{
			getCharacterByOrder(i).spriteColour = SpriteColor::Blue;
			getCharacterByOrder(i).textureUpdate();
			getCharacterByOrder(i).movementStepSize = 1;
		}
		else
		{
			getCharacterByOrder(i).spriteColour = SpriteColor::Default;
			getCharacterByOrder(i).textureUpdate();
		}
	}
	// When everyone is out of the water and centered on the grid, back to fast movement.
	
	if (getCharacterByOrder(1).spriteColour == SpriteColor::Default &&
		getCharacterByOrder(2).spriteColour == SpriteColor::Default &&
		getCharacterByOrder(3).spriteColour == SpriteColor::Default &&
		getCharacterByOrder(4).spriteColour == SpriteColor::Default &&
		intify(getCharacterByOrder(1).sprite.getPosition().x) % (getTilePixels()) == 0 &&
		intify(getCharacterByOrder(1).sprite.getPosition().y) % (getTilePixels()) == 0
		)
	{
		if (getCharacterByOrder(1).coordVector.size() > 16)
		{
			const int resize{ 64 / getCharacterByOrder(1).movementStepSize - 16 };

			getCharacterByOrder(1).coordVector.erase(getCharacterByOrder(1).coordVector.begin(), getCharacterByOrder(1).coordVector.begin() + resize);
			getCharacterByOrder(2).coordVector.erase(getCharacterByOrder(2).coordVector.begin(), getCharacterByOrder(2).coordVector.begin() + resize);
			getCharacterByOrder(3).coordVector.erase(getCharacterByOrder(3).coordVector.begin(), getCharacterByOrder(3).coordVector.begin() + resize);
			getCharacterByOrder(4).coordVector.erase(getCharacterByOrder(4).coordVector.begin(), getCharacterByOrder(4).coordVector.begin() + resize);
		}

		getCharacterByOrder(1).movementStepSize = 4;
		getCharacterByOrder(2).movementStepSize = 4;
		getCharacterByOrder(3).movementStepSize = 4;
		getCharacterByOrder(4).movementStepSize = 4;
	}
}
void Window::drawSprites()
{
	// get values from View class
	int pixelSize{ getPixelSize() };

	for (size_t i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i].setPosition(pairF(spriteVector[i].getPosition().x, spriteVector[i].getPosition().y - (8 * pixelSize)));
		this->draw(spriteVector[i]);
		spriteVector[i].setPosition(pairF(spriteVector[i].getPosition().x, spriteVector[i].getPosition().y + (8 * pixelSize)));
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
	// get values from View class
	int pixelSize{ getPixelSize() };
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
	// get values from View class
	int pixelSize{ getPixelSize() };

	noise.move(direction);
	sf::Vector2f noiseOrigin = noise.getPosition();

	if (noise.getPosition().x < noise.getSize().x * -pixelSize)
	{
		noise.setPosition(direction.x, noise.getPosition().y);
		noiseOrigin = noise.getPosition();
	}
	else if (noise.getPosition().x > noise.getSize().x * pixelSize)
	{
		noise.setPosition(-direction.x, noise.getPosition().y);
		noiseOrigin = noise.getPosition();
	}
	if (noise.getPosition().y < noise.getSize().y * -pixelSize)
	{
		noise.setPosition(noise.getPosition().x, direction.y);
		noiseOrigin = noise.getPosition();
	}
	else if (noise.getPosition().y > noise.getSize().y * pixelSize)
	{
		noise.setPosition(noise.getPosition().x, -direction.y);
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
void Window::drawFullSimplex(sf::Vector2f direction)
{
	if (menu.menuEnabled()) { direction = pairF(0, 0); }

	// get values from View class
	int pixelSize{ getPixelSize() };

	noise.setScale(sf::Vector2f(pixelSize, pixelSize));

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

// Flow Functions
bool justOnce{ true }; // for screenshots
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
	// get values from View class
	int pixelSize{ getPixelSize() };
	water.noise.noise.setScale(pixelSize, pixelSize);
	// Is automatic, prints on tiles 89 and 90.
	if (!menu.menuEnabled()) { water.update(); }

	//FontMap waterTileMap;
	//waterTileMap.load(water.waterAnimationFrames, sf::Vector2u(32, 32), water.westKagarWater, TILES_PER_CHUNK_X * 4, TILES_PER_CHUNK_Y * 4);
	//draw(waterTileMap);
	
	// change to vertexbuffer ?
	for (int i = 0; i < TILES_PER_CHUNK_X * 4; i++)
	{
		for (int j = 0; j < TILES_PER_CHUNK_Y * 4; j++)
		{
			if (water.westKagarWater[i + j * (TILES_PER_CHUNK_X * 4)])
			{
				water.noise.noise.setPosition(water.width * pixelSize * i, water.height * pixelSize * j);
				draw(water.noise.noise);
			}
		}
	}

	//reset
	water.noise.noise.setPosition(0, 0);

}

// Text Functions
void Window::addDevToolsText()
{
	std::string longString{ "But I must explain to you how all this mistaken idea of denouncing pleasure and praising pain was born and I will give you a complete account of the system, and expound the actual teachings of the great explorer of the truth, the masterbuilder of human happiness. No one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful." }; 
	//std::string longString{ "I want nachos. They will be made. I will put cheese on them because that's what makes nachos nachos. NACHOS. What else do you want on them? Onions? No onions. No veggies. Only quiche, yams, and meaty nachos." };
	//std::string longString{ "Hey! How's it going? Let's test these chars! Oh yeah! Hello, allowed, initiate..." };
	textBox.box.setColor(sf::Color::Black);
	textBox.box.setAlpha(150);
	addText(longString, pairF(250, 250), 1, 800);

	int devToolsTextSize{ 2 };
	addText("FPS: " + this->DEV_TOOLS.getFPS(), getViewCoordinates(UL), devToolsTextSize, 0, true, true, true);
	addText("LASTY", getViewCoordinates(DR), devToolsTextSize, 0, true, true, true);
	addText("X: " + stringify(getGridPosition().x) + ", Y :" + stringify(getGridPosition().y), getViewCoordinates(UR), devToolsTextSize, 0, true, true, true);
	if (this->DEV_TOOLS.wallToggleBool) { addText("NO WALLS", getViewCoordinates(DL), devToolsTextSize, 0, true, true, true); }
}
void Window::addText(std::string string, sf::Vector2f startPosition, int scale, int boundingWidth, bool background, bool borders, bool important)
{
	if (important) { importantTextBox.addText(string, startPosition, scale, boundingWidth, background, borders); }
	else { textBox.addText(string, startPosition, scale, boundingWidth, background, borders); }
}
void Window::drawText()
{
	// In this case, menu will need it's own text class, too. Or - it can use important without borders and backgrounds.
	if (!menu.menuEnabled())
	{
		for (size_t i = 0; i < textBox.box.spriteContainerBlack.size(); i++) { this->draw(textBox.box.spriteContainerBlack[i]); }
		this->draw(textBox.box.borderBlack);
		this->draw(textBox.box.background);
		this->draw(textBox.box.border);
		for (size_t i = 0; i < textBox.box.spriteContainer.size(); i++) { this->draw(textBox.box.spriteContainer[i]); }
		for (size_t i = 0; i < textBox.fontContainer.size(); i++) { this->draw(textBox.fontContainer[i]); }
	}
	textBox.emptyContainers();

	for (size_t i = 0; i < importantTextBox.box.spriteContainerBlack.size(); i++) { this->draw(importantTextBox.box.spriteContainerBlack[i]); }
	this->draw(importantTextBox.box.borderBlack);
	this->draw(importantTextBox.box.background);
	this->draw(importantTextBox.box.border);
	for (size_t i = 0; i < importantTextBox.box.spriteContainer.size(); i++) { this->draw(importantTextBox.box.spriteContainer[i]); }
	for (size_t i = 0; i < importantTextBox.fontContainer.size(); i++) { this->draw(importantTextBox.fontContainer[i]); }
	importantTextBox.emptyContainers();
}

// Menu Functinos
void Window::drawMenu()
{
	if (menu.menuEnabled())
	{
		menu.createMenu();

		for (size_t i = 0; i < menu.menuBox.box.spriteContainerBlack.size(); i++) { this->draw(menu.menuBox.box.spriteContainerBlack[i]); }
		this->draw(menu.menuBox.box.borderBlack);
		this->draw(menu.menuBox.box.background);
		this->draw(menu.menuBox.box.border);
		for (size_t i = 0; i < menu.menuBox.box.spriteContainer.size(); i++) { this->draw(menu.menuBox.box.spriteContainer[i]); }
		for (size_t i = 0; i < menu.menuBox.fontContainer.size(); i++) { this->draw(menu.menuBox.fontContainer[i]); }
		menu.menuBox.emptyContainers();

		for (size_t i = 0; i < menu.alertBox.box.spriteContainerBlack.size(); i++) { this->draw(menu.alertBox.box.spriteContainerBlack[i]); }
		this->draw(menu.alertBox.box.borderBlack);
		this->draw(menu.alertBox.box.background);
		this->draw(menu.alertBox.box.border);
		for (size_t i = 0; i < menu.alertBox.box.spriteContainer.size(); i++) { this->draw(menu.alertBox.box.spriteContainer[i]); }
		for (size_t i = 0; i < menu.alertBox.fontContainer.size(); i++) { this->draw(menu.alertBox.fontContainer[i]); }
		menu.alertBox.emptyContainers();

	}
}