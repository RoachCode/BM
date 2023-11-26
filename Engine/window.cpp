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
	//viewX = intify(view.getCenter().x);
	//viewY = intify(view.getCenter().y);
	//viewOriginX = viewX;
	//viewOriginY = viewY;
	movementStepSize = 4 * windowScale;
	tileSize = 32 * windowScale;

	Noise::m_initSimplex(size.x / windowScale, size.y / windowScale, 4);


}

void Window::pollEvents()
{

	/*
	if (pos.x % 64 == 0 && pos.y % 64 == 0)
	{
		if (up && pos.y > 0)
		{
			//view.move(0, -movementStepSize);
			sprite.spriteVector[0].setPosition(pos.x, pos.y - movementStepSize);
			mostRecentDirection = UP;
		}
		else if (down && pos.y < 14 * 4 * 64)
		{
			//view.move(0, movementStepSize);
			sprite.spriteVector[0].setPosition(pos.x, pos.y + movementStepSize);
			mostRecentDirection = DOWN;
		}
		else if (left && pos.x > 0)
		{
			//view.move(-movementStepSize, 0);
			sprite.spriteVector[0].setPosition(pos.x - movementStepSize, pos.y);
			mostRecentDirection = LEFT;
		}
		else if (right && pos.x < 24 * 4 * 64)
		{
			//view.move(movementStepSize, 0);
			sprite.spriteVector[0].setPosition(pos.x + movementStepSize, pos.y);
			mostRecentDirection = RIGHT;
		}

	}
	else
	{
		if (pos.y % 64 != 0)
		{
			if (mostRecentDirection == UP)
			{
				//view.move(0, -movementStepSize);
				sprite.spriteVector[0].setPosition(pos.x, pos.y - movementStepSize);
				if (pos.y % 64 == 0) { up = false; }
			}
			else if (mostRecentDirection == DOWN)
			{
				//view.move(0, movementStepSize);
				sprite.spriteVector[0].setPosition(pos.x, pos.y + movementStepSize);
				if (pos.y % 64 == 0) { down = false; }
			}
		}
		else if (pos.x % 64 != 0)
		{
			if (mostRecentDirection == LEFT)
			{
				//view.move(-movementStepSize, 0);
				sprite.spriteVector[0].setPosition(pos.x - movementStepSize, pos.y);
				if (pos.x % 64 == 0) { left = false; }
			}
			else if (mostRecentDirection == RIGHT)
			{
				//view.move(movementStepSize, 0);
				sprite.spriteVector[0].setPosition(pos.x + movementStepSize, pos.y);
				if (pos.x % 64 == 0) { right = false; }
			}
		}
	}
	*/
	//this->setView(view);
	
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
void Window::pollMovement()
{
	sf::Vector2i pos{ pairI(intify(sprite.spriteVector[0].getPosition().x), intify(sprite.spriteVector[0].getPosition().y)) };
	if (pos.x % tileSize == 0 && pos.y % tileSize == 0)
	{
		if (up)
		{
			sprite.spriteVector[0].move(0, -movementStepSize);
			changeFalseLastKeyState(lastKeyUp);
		}
		else if (down)
		{
			sprite.spriteVector[0].move(0, movementStepSize);
			changeFalseLastKeyState(lastKeyDown);
		}
		else if (left)
		{
			sprite.spriteVector[0].move(-movementStepSize, 0);
			changeFalseLastKeyState(lastKeyLeft);
		}
		else if (right)
		{
			sprite.spriteVector[0].move(movementStepSize, 0);
			changeFalseLastKeyState(lastKeyRight);
		}
	}
	else
	{
		if (pos.x % tileSize != 0)
		{
			if (lastKeyRight)
			{
				sprite.spriteVector[0].move(movementStepSize, 0);
			}
			else if (lastKeyLeft)
			{
				sprite.spriteVector[0].move(-movementStepSize, 0);
			}
		}
		else if (pos.y % tileSize != 0)
		{
			if (lastKeyUp)
			{
				sprite.spriteVector[0].move(0, -movementStepSize);
			}
			else if (lastKeyDown)
			{
				sprite.spriteVector[0].move(0, movementStepSize);
			}
		}
	}


}

void Window::drawSprites()
{
	sprite.spriteVector[0].move(0, (-8 * windowScale)); // Move characters up
	for (auto i : sprite.spriteVector)
	{
		this->draw(i);
	}
	sprite.spriteVector[0].move(0, (8 * windowScale)); // Move characters down
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