#pragma once
#include "window.h"
#include <iostream>
#include <random> // for drawing because I dont have the freakin particles calibrated yet.

// Call constructor, which calls inherited constructor from sf::RenderWindow
Window::Window()
	: sf::RenderWindow(sf::VideoMode(0, 0, 32U), "Lockestone Chronicles", sf::Style::Fullscreen)
{
	// Get the size of the window
	Window::size = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	this->setVerticalSyncEnabled(false); // must be disabled for DevTools fps counter to work
	this->setKeyRepeatEnabled(false); // easier to set eg movement states by checking press and release states
	// Assign current view to Window::view
	Window::view = this->getDefaultView();
	// Sets the view to the appropriate zoom level for display
	windowScale = 1;
	while (size.x > (MAP_WIDTH_PIXELS * windowScale * 2))
	{
		windowScale *= 2;
	}
	this->setView(Window::view);
	isMovingView = false;

	renderWindowSprites.create(32 * 24 * 4, 32 * 14 * 4);
	pseudoWindowSprites.setSize(sf::Vector2f(32 * 24 * 4, 32 * 14 * 4));

	this->initSimplex(size.x / 2, size.y / 2, 4);

	flowWindowTexture.create(flow.gridSize.x, flow.gridSize.y);
	flowWindow.setSize(sf::Vector2f(flow.gridSize.x, flow.gridSize.y));
	flowWindowTexture.clear(sf::Color(0, 0, 0, 255));
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
				startViewMovement(sf::Vector2f(0, 1));
				break;
			case sf::Keyboard::Right:
				startViewMovement(sf::Vector2f(1, 0));
				break;
			case sf::Keyboard::Left:
				startViewMovement(sf::Vector2f(-1, 0));
				break;
			case sf::Keyboard::Up:
				startViewMovement(sf::Vector2f(0, -1));
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
				this->draw(font.charSprite); // huge bottleneck
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
	imageHandler.pseudoWindow.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(imageHandler.pseudoWindow);
}

void Window::drawTileMapsFront()
{
	imageHandler.pseudoWindow2.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(imageHandler.pseudoWindow2);
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
	renderWindowSprites.clear(sf::Color(0, 0, 0, 0));

	for (auto i : sprite.shapeVector)
	{
		renderWindowSprites.draw(i);
	}


	renderWindowSprites.display();
	pseudoWindowSprites.setTexture(&renderWindowSprites.getTexture());
	pseudoWindowSprites.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(pseudoWindowSprites);

}

void Window::drawParticles()
{
	//particle system test
	particles.setColor
	(
		sf::Color::Red,
		sf::Color::Black,
		sf::Color::Red,
		sf::Color::Black
	);

	sf::Time elapsed = particles.clock.restart();
	particles.update(elapsed);
	draw(particles);

}

void Window::drawParticles2()
{
	//particle system test
	particles2.setColor
	(
		sf::Color::Red,
		sf::Color::Black,
		sf::Color::Red,
		sf::Color::Black
	);

	sf::Time elapsed = particles2.clock.restart();
	particles2.update(elapsed);
	draw(particles2);

}

void Window::drawSimplex(int direction)
{
	simplexSpeed++;
	sf::Image perlinImage;
	const float x{ simplexSizeX };
	const float y{ simplexSizeY };

	if (simplexSpeed > 3)
	{
		simplexSpeed = 0;
		std::vector<sf::Uint8> blendData;
		std::vector<sf::Uint8> vertLineStart;
		switch (direction)
		{
		case UP:
			// Transform - Up
			for (int i = 0; i < x; i++)
			{

				blendData.push_back(simplexData[0]);
				simplexData.pop_front();
			}
			for (int i = 0; i < blendData.size(); i++)
			{
				simplexData.push_back(blendData[i]);
			}
			break;
		case DOWN:
			// Transform - Down
			for (int i = 0; i < x; i++)
			{
				blendData.push_back(simplexData.back());
				simplexData.pop_back();
			}
			for (int i = 0; i < blendData.size(); i++)
			{
				simplexData.push_front(blendData[i]);
			}
			break;
		case LEFT:
			// Transform - Left
			for (int j = 0; j < y; j++)
			{
				for (int i = 0; i < x; i++)
				{
					blendData.push_back(simplexData[i + j * x]);
				}
				std::rotate(blendData.begin(), blendData.begin() + 1, blendData.end());
				for (int i = 0; i < x; i++)
				{
					simplexData[i + j * x] = blendData[i];
				}
				blendData.clear();
			}
			blendData.clear();
		case RIGHT:
			// Transform - Right
			for (int j = 0; j < y; j++)
			{
				for (int i = 0; i < x; i++)
				{
					blendData.push_back(simplexData[i + j * x]);
				}
				std::rotate(blendData.begin(), blendData.end() - 1, blendData.end());
				for (int i = 0; i < x; i++)
				{
					simplexData[i + j * x] = blendData[i];
				}
				blendData.clear();
			}
			blendData.clear();
		default:
			blendData.clear();
			break;
		}
	}

	noise.setSize(sf::Vector2f(x, y));
	sf::Uint8* pixels = new sf::Uint8[x * y * 4];
	for (int i = 0; i < x * y; i++)
	{
		sf::Uint8 mutate{ simplexData[i] };
		pixels[(i * 4) + 0] = mutate;
		pixels[(i * 4) + 1] = mutate;
		pixels[(i * 4) + 2] = mutate;
		pixels[(i * 4) + 3] = 255;

	}
	perlinImage.create(x, y, pixels);
	delete[] pixels;
	noiseTexture.loadFromImage(perlinImage);
	noise.setTexture(&noiseTexture);
	
	noise.setScale(sf::Vector2f(windowScale, windowScale));
	this->draw(noise);
}

void Window::createSimplexValues(int x, int y)
{
	xyValues.clear();
	int octave{ 8 };
	float x1 = 0;
	float x2 = 1;
	float y1 = 0;
	float y2 = 1;
	for (int k = 0; k < simplexOctaves; k++)
	{
		octave *= 2;
		for (int iy = 0; iy < y; ++iy)
		{
			for (int ix = 0; ix < x; ++ix)
			{
				// these offsets define the circles
				float s = static_cast<float>(ix) / static_cast<float>(x);
				float t = static_cast<float>(iy) / static_cast<float>(y);

				// clamping to [0, 1]
				float dx = x2 - x1;
				float dy = y2 - y1;

				// 4d noise. two orthogonal 3d cylinders. Loops continuously along x and y dimensions.
				float modX = x1 + cos(s * 2 * PI) * dx / (2 * PI / octave);
				float modY = y1 + cos(t * 2 * PI) * dy / (2 * PI / octave);
				float modZ = x1 + sin(s * 2 * PI) * dx / (2 * PI / octave);
				float modW = y1 + sin(t * 2 * PI) * dy / (2 * PI / octave);
				// todo: make one dimension alterable to be for time. or, add values from a circle of noise to make a time loop.

				xyValues.push_back(modX);
				xyValues.push_back(modY);
				xyValues.push_back(modZ);
				xyValues.push_back(modW);
			}
		}
	}
	octave = 8;
}

void Window::normalizeRGB()
{
	int lowest{ 0 };
	int highest{ 0 };
	for (int i = 0; i < tempContainer.size(); i++)
	{

		if (tempContainer[i] < lowest) { lowest = tempContainer[i]; }
		if (tempContainer[i] > highest) { highest = tempContainer[i]; }
	}
	//std::cout << "lowest: " << lowest << "     Highest: " << highest << '\n';
	for (int i = 0; i < tempContainer.size(); i++)
	{
		tempContainer[i] += abs(lowest);
		if (tempContainer[i] > 255) { tempContainer[i] = 255; }

		//std::cout << noiseInt << '\n';
		sf::Uint8 noiseUint = sf::Uint8(tempContainer[i]);
		simplexData.push_back(noiseUint);
	}
}

void Window::initSimplex(float sizeX, float sizeY, int octaves)
{
	OpenSimplexNoise::Noise simplex(494358);
	simplexOctaves = octaves;
	simplexSizeX = sizeX;
	simplexSizeY = sizeY;

	const float x{ sizeX };
	const float y{ sizeY };
	createSimplexValues(x, y);
	tempContainer.clear();

	for (int i = 0; i < x * y; i++)
	{
		double noise{ 0.0 };
		for (int j = 0; j < simplexOctaves; j++)
		{
			//std::cout << simplex.eval(static_cast<double>(xyValues[i + x * y * j].x), static_cast<double>(xyValues[i + x * y * j].y)) << '\n';+
			const double modX{ static_cast<double>(xyValues[(i * 4 + 0) + 4 * x * y * j]) };
			const double modY{ static_cast<double>(xyValues[(i * 4 + 1) + 4 * x * y * j]) };
			const double modZ{ static_cast<double>(xyValues[(i * 4 + 2) + 4 * x * y * j]) };
			const double modW{ static_cast<double>(xyValues[(i * 4 + 3) + 4 * x * y * j]) };

			noise += simplex.eval(modX, modY, modZ, modW) / (j + 1);

		}


		noise *= (255.999 / simplexOctaves);
		//std::cout << noise << '\n';
		// need to correct for the noise having 1.5x the value it should, for some reason.
		//noise = (noise * 2) / 3;
		int noiseInt = static_cast<int>(noise);	
		tempContainer.push_back(noiseInt);

	}
	normalizeRGB();

}


void Window::drawFlow(FlowPreset& fp)
{
	sf::Color initialColor = sf::Color(fp.red, fp.green, fp.blue, fp.alpha);
	const int yPaths{ fp.xCount };
	const int xPaths{ fp.yCount };

	sf::Vector2f returnPos;
	float angle;
	float initialRadius;
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator

	// Draw Grid
	if (drawGrid)
	{
		flowWindowTexture.draw(flow.m_vertices);
	}
	// Draw Compass Needles
	if (drawNeedles)
	{
		for (unsigned int j = 0; j < flow.gridSize.y / flow.tileSize.y; j++)
		{
			for (unsigned int i = 0; i < flow.gridSize.x / flow.tileSize.x; i++)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &flow.m_vertices[(i + j * (flow.gridSize.y / flow.tileSize.y)) * 4];

				angle = flow.angleVector[i + j * (flow.gridSize.x / flow.tileSize.x)];

				const sf::Vector2f quadCenter = sf::Vector2f(quad[2].position.x - (flow.tileSize.x / 2), quad[2].position.y - (flow.tileSize.y / 2));
				flow.line.setPosition(quadCenter);
				flow.line.setRotation(angle);

				quad = nullptr; // ?
				flowWindowTexture.draw(flow.line);
			}
		}
	}
	// Draw paths
	if (drawLines)
	{
		for (int ii = 0; ii < xPaths; ii++)
		{
			for (int iii = 0; iii < yPaths; iii++)
			{
				//random distribution
				//std::uniform_int_distribution<> distr(0, flow.gridSize.x); // define the range
				//int rdmX = distr(gen); // generate numbers
				//std::uniform_int_distribution<> distr2(0, flow.gridSize.y); // define the range
				//int rdmY = distr(gen);

				//even distribution
				// I think I can offset these values in a loop. draw an imaginary circle. loop the noise
				const int startPosX{ static_cast<int>(flow.tileSize.x / 2) + static_cast<int>(ii * (static_cast<int>(flow.gridSize.x) / xPaths) + (static_cast<int>(flow.gridSize.x) / xPaths) / 2) };
				const int startPosY{ static_cast<int>(flow.tileSize.y / 2) + static_cast<int>(iii * (static_cast<int>(flow.gridSize.y) / yPaths) + (static_cast<int>(flow.gridSize.y) / yPaths) / 2) };

				if (pathCounter == 0)
				{
					flow.tracer.setPosition(startPosX, startPosY);
					returnPos = flow.tracer.getPosition();
					initialRadius = flow.tracer.getRadius();
				}

				if (pathCounter < fp.plottedPoints)
				{
					pathCounter++;
					fp.applyChanges(flow);

					// Gets the angle from the current position's underlying grid
					const sf::Vector2f pos(flow.tracer.getPosition());
					const int gridX{ static_cast<int>(floatify(pos.x) / floatify(flow.tileSize.x)) };
					const int gridY{ static_cast<int>(floatify(pos.y) / floatify(flow.tileSize.y)) };
					angle = flow.angleVector[gridX + gridY * (flow.gridSize.x / flow.tileSize.x)];

					// Converts the angle to x,y coordinates and moves the tracer
					const float newX = cos(angle * (PI / 180));
					const float newY = sin(angle * (PI / 180));
					flow.tracer.move(newX * fp.stepSize, newY * fp.stepSize);

					// Bounds the tracer to the drawing area
					if (flow.tracer.getPosition().x < flow.gridSize.x - 1 && flow.tracer.getPosition().y < flow.gridSize.y - 1)
					{
						flowWindowTexture.draw(flow.tracer);
						dotCounter++;
					}
				}
				else
				{
					flow.tracer.setPosition(returnPos);
					flow.tracer.setRadius(initialRadius);
					flow.tracer.setFillColor(initialColor);
					pathCounter = 0;
				}

			}
		}
	}
	if (dotCounter > static_cast<int>(fp.plottedPoints * (xPaths - 1) * (yPaths - 1)))
	{
		drawGrid = false;
		drawNeedles = false;
		drawLines = false;
		this->draw(flowWindow);

		if (onlyOnceHack)
		{

			std::string filename = flow.currentName + ".bmp";
			if (!flowWindowTexture.getTexture().copyToImage().saveToFile(filename))
			{
				std::cout << "screenshot failed";
			}
			onlyOnceHack = false;
		}
	}
	if (drawGrid || drawNeedles || drawLines)
	{
		flowWindowTexture.display();
		flowWindow.setTexture(&flowWindowTexture.getTexture());
		this->draw(flowWindow);
		//flowWindowTexture.clear();
	}
}