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
		//spriteVector[i].setPosition(pairF(spriteVector[i].getPosition().x, spriteVector[i].getPosition().y - (8 * pixelSize)));
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
	// get values from View class
	int pixelSize{ getPixelSize() };

	noise.setScale(sf::Vector2f(pixelSize, pixelSize));


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
	water.update();

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
void Window::drawDevToolsText()
{
	drawText("FPS: " + this->DEV_TOOLS.getFPS(), getViewCoordinates(UL), 2);
	drawText("X: " + stringify(getGridPosition().x) + ", Y :" + stringify(getGridPosition().y), getViewCoordinates(UR), 2);
	//std::string longString{ "But I must explain to you how all this mistaken idea of denouncing pleasure and praising pain was born and I will give you a complete account of the system, and expound the actual teachings of the great explorer of the truth, the masterbuilder of human happiness. No one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful. Nor again is there anyone who loves or pursues or desires to obtain pain of itself, because it is pain, but because occasionally circumstances occur in which toil and pain can procure him some great pleasure. To take a trivial example, which of us ever undertakes laborious physical exercise, except to obtain some advantage from it? But who has any right to find fault with a man who chooses to enjoy a pleasure that has no annoying consequences, or one who avoids a pain that produces no resultant pleasure?" }; 
	//drawText(longString, pairF(250, 250), 1, 800);
	if (this->DEV_TOOLS.wallToggleBool) { drawText("NO WALLS", getViewCoordinates(DL), 2); }
}

/*
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
*/

void Window::drawText(std::string string, sf::Vector2f startPosition, int scale, int boundingWidth)
{
	// get values from View class
	int pixelSize{ getPixelSize() };

	// init, scale and bounding
	font.currentString.clear();
	//if (boundingWidth == 0) { boundingWidth = size.x - startPosition.x; } // the visible screen
	//if (boundingWidth < 0) { boundingWidth = 0; }
	const int fontScale{ scale * pixelSize };

	// tiles are two pixels wide
	int maxTilesPerRow{ (boundingWidth == 0) ? 0 : boundingWidth / (2 * fontScale) };

	// create text
	for (size_t j = 0; j < string.length(); j++)
	{
		const char letter = string[j];
		const int letterNumber{ font.getRectOffset(letter) };
		if (font.getRectOffset(letter) < 207)
		{
			font.currentString.push_back(letterNumber + 0);
			font.currentString.push_back(letterNumber + 1);
			font.currentString.push_back(letterNumber + 2);
		}
		else if (font.getRectOffset(letter) < 231)
		{
			font.currentString.push_back(letterNumber + 0);
			font.currentString.push_back(letterNumber + 1);
			font.currentString.push_back(letterNumber + 2);
			font.currentString.push_back(letterNumber + 3);
		}
		else
		{
			font.currentString.push_back(letterNumber + 0);
		}
		// kerning space (2 pixels)
		if (j < string.length() - 1 && letter != ' ') { font.currentString.push_back(78); }

		// check to see if the word will fit on this row (including following punctuation)
		if (string[j] == ' ' && maxTilesPerRow != 0)
		{
			int tilesInWord{ 4 }; //starts with a space. supposed to be 3 but this works for some reason.
			int iterator{ 1 };
			while (string[j + iterator] != ' ' && j + iterator < string.length())
			{
				if (font.getRectOffset(letter) < 207)
				{
					tilesInWord += 3;
				}
				else if (font.getRectOffset(letter) < 231)
				{
					tilesInWord += 4;
				}
				else
				{
					tilesInWord += 1;
				}
				//kerning if the word isn't finished
				if (string[j + iterator + 1] != ' ')
				{
					tilesInWord += 1;
				}
				iterator += 1;
			}

			// get current position in the line
			int tilePosition{ intify(font.currentString.size()) };
			while (tilePosition > maxTilesPerRow) { tilePosition -= maxTilesPerRow; }

			// if the word won't fit, use kerning spaces to finish the line
			if (tilePosition + tilesInWord > maxTilesPerRow)
			{
				int remainingTiles{ maxTilesPerRow - tilePosition };
				for (int i = 0; i < remainingTiles; i++) { font.currentString.push_back(78); }
			}
		}
	}

	// add blank characters to the end to complete the tilemap or shrink to fit
	int messageTileCount{ intify(font.currentString.size()) };
	int messageWidthInTiles{ messageTileCount > maxTilesPerRow && maxTilesPerRow != 0 ? maxTilesPerRow : messageTileCount };
	int messageWidthInPixels{ messageWidthInTiles * 2 * fontScale + fontScale };
	if (messageWidthInPixels < boundingWidth) { boundingWidth = messageWidthInPixels; }

	// If no bounding box was specified, stay in the view.
	if (maxTilesPerRow == 0)
	{
		maxTilesPerRow = messageTileCount;
		boundingWidth = messageWidthInPixels;
		// Bounds Right
		if ((intify(startPosition.x) + messageWidthInPixels) > intify(getViewCoordinates(UR).x))
		{
			startPosition.x = floatify(getViewCoordinates(UR).x - messageWidthInPixels);
		}
		// Bounds Left
		if (intify(startPosition.x) < getViewCoordinates(UL).x)
		{
			startPosition.x = getViewCoordinates(UL).x;
		}
		// Bounds Bottom
		if (intify(startPosition.y) + 10 > intify(getViewCoordinates(DR).y))
		{
			startPosition.y = floatify(getViewCoordinates(DR).y - (10 * fontScale) - fontScale);
		}
		// Bounds Top
		if (intify(startPosition.y) < getViewCoordinates(UL).y)
		{
			startPosition.y = getViewCoordinates(UL).y;
		}
	}
	while (messageTileCount % maxTilesPerRow != 0)
	{
		font.currentString.push_back(78);
		messageTileCount += 1;
	}
	int messageRows{ messageTileCount / maxTilesPerRow};

	// creates background to show text bounds are working properly (for testing)
	sf::RectangleShape tempbg(pairF(boundingWidth, messageRows * 10 * fontScale + fontScale)); // + pixelsize is for shadow
	tempbg.setPosition(startPosition);
	tempbg.setFillColor(sf::Color(0, 100, 200, 105));
	draw(tempbg);
	
	// prints characters.
	for (int i = 0; i <= 1; i++)
	{
		// Runs twice to set a shadow effect
		if (i == 0)
		{
			font.setColor(sf::Color(44, 44, 44), true);
			font.fontMap.setPosition(pairF(startPosition.x + fontScale, startPosition.y + fontScale));
		}
		else
		{
			font.setColor(sf::Color(font.textRed, font.textGreen, font.textBlue));
			font.fontMap.setPosition(startPosition);
		}
		font.fontMap.load(font.fontImage, sf::Vector2u(2, 10), font.currentString, messageWidthInTiles, messageRows);
		font.fontMap.setScale(pairF(fontScale, fontScale));
		draw(font.fontMap);
	}
}