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
	while (Window::view.getSize().x > MAP_WIDTH_PIXELS * 2)
	{
		Window::view.setSize(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
		Window::view.setCenter(floatify(Window::view.getSize().x / 2), floatify(Window::view.getSize().y / 2));
	}
	this->setView(Window::view);
	isMovingView = false;

	renderWindowSprites.create(32 * 24 * 4, 32 * 14 * 4);
	pseudoWindowSprites.setSize(sf::Vector2f(32 * 24 * 4, 32 * 14 * 4));

	this->initSimplex();
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

int Window::getZoomFactor()
{
	return static_cast<int>(size.x / view.getSize().x);
}

void Window::drawText(std::string string, sf::Vector2f startPosition)
{
	font.setStartPos(startPosition);
	font.setPos(font.getStartPos());
	int pixelWidth{ static_cast<int>(font.moveR.x) * static_cast<int>(string.length()) };
	// bounds on the right. so far only right side.
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
	this->draw(imageHandler.pseudoWindow);
}

void Window::drawTileMapsFront()
{
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

void Window::drawSimplex(int direction)
{
	simplexSpeed++;
	sf::Image perlinImage;
	const float x{ view.getSize().x };
	const float y{ view.getSize().y };



	if (simplexSpeed > 5)
	{
		simplexSpeed = 0;
		std::vector<sf::Uint8> blendData;
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
		pixels[(i * 4) + 3] = 255 - mutate;

	}
	perlinImage.create(x, y, pixels);
	delete[] pixels;
	noiseTexture.loadFromImage(perlinImage);
	noise.setTexture(&noiseTexture);
	
	this->draw(noise);
}

void Window::createSimplexValues(int x, int y)
{
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
	for (int i = 0; i < tempContainer.size(); i++)
	{

		if (tempContainer[i] < lowest) { lowest = tempContainer[i]; }

	}
	for (int i = 0; i < tempContainer.size(); i++)
	{
		tempContainer[i] += abs(lowest);
		if (tempContainer[i] > 255) { tempContainer[i] = 255; }

		//std::cout << noiseInt << '\n';
		sf::Uint8 noiseUint = sf::Uint8(tempContainer[i]);
		simplexData.push_back(noiseUint);
	}
}

void Window::initSimplex()
{
	OpenSimplexNoise::Noise simplex(494358);
	simplexOctaves = 4;
	const float x{ view.getSize().x };
	const float y{ view.getSize().y };
	createSimplexValues(x, y);
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
		noise *= 255.999 / simplexOctaves; //
		int noiseInt = static_cast<int>(noise);

		tempContainer.push_back(noiseInt);

	}
	normalizeRGB();

}

void Window::drawFlow()
{


	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, view.getSize().x); // define the range

	const int rdmX = distr(gen); // generate numbers
	std::uniform_int_distribution<> distr2(0, view.getSize().y); // define the range
	const int rdmY = distr(gen);

	flow.tracer.setPosition(rdmX, rdmY);

	const sf::Vector2f returnPos = flow.tracer.getPosition();
	float angle;
	for (unsigned int i = 0; i < flow.width / flow.tileSize.x; i++)
	{
		for (unsigned int j = 0; j < flow.height / flow.tileSize.y; j++)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &flow.m_vertices[(i + j * flow.width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * flow.tileSize.x, j * flow.tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * flow.tileSize.x, j * flow.tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * flow.tileSize.x, (j + 1) * flow.tileSize.y);
			quad[3].position = sf::Vector2f(i * flow.tileSize.x, (j + 1) * flow.tileSize.y);

			quad[0].color = sf::Color(0, 255, 0, 35);
			quad[1].color = sf::Color(0, 0, 0, 35);
			quad[2].color = sf::Color(0, 155, 0, 35);
			quad[3].color = sf::Color(0, 0, 0, 35);

			angle = flow.angleVector[j + i * (flow.height / flow.tileSize.y)];
			//float angle = j * PI;

			const sf::Vector2f quadCenter = sf::Vector2f(quad[2].position.x - (flow.tileSize.x / 2), quad[2].position.y - (flow.tileSize.y / 2));
			flow.line.setPosition(quadCenter);
			flow.line.setRotation(angle);

			draw(flow.line);
		}
	}

	for (unsigned int i = 0; i < flow.width * flow.height; i++)
	{

		const sf::Vector2f pos(flow.tracer.getPosition());
		const int gridX = pos.x / flow.tileSize.x;
		const int gridY = pos.y / flow.tileSize.y;

		angle = flow.angleVector[gridY + gridX * (flow.height / flow.tileSize.y)];

		const float newX = cos(angle * (PI / 180));
		const float newY = sin(angle * (PI / 180));

		flow.tracer.move(newX, newY);
		draw(flow.tracer);
		
	}
	flow.tracer.setPosition(returnPos);
	draw(flow.m_vertices);

}