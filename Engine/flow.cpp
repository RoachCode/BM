#pragma once
#include "flow.h"

// Public
FlowPreset::FlowPreset(int n, float r, float g, float b, float a, int pp, float ss, int xcount, int ycount) :
	name(n),
	red(r),
	green(g),
	blue(b),
	alpha(a),
	plottedPoints(pp),
	stepSize(ss),
	xCount(xcount),
	yCount(ycount)
{
	ppCounter = 0;
};

// Public
Flow::Flow()
{
	// Set defaults
	m_drawGrid = false;
	m_drawNeedles = false;
	m_drawLines = true;
	const int gridFactor{ 100 };
	
	m_width = sf::VideoMode::getDesktopMode().width;
	m_height = sf::VideoMode::getDesktopMode().height;
	tileSize = sf::Vector2u(m_width / gridFactor, m_height / gridFactor); // defines the density of the grid
	gridSize = sf::Vector2u(static_cast<unsigned int>(tileSize.x) * gridFactor, static_cast<unsigned int>(tileSize.y) * gridFactor);
	
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(gridSize.x * gridSize.y * 4);
	m_line.setSize(sf::Vector2f(m_height / 50 / 2, 1));
	m_initSimplex(gridSize.x / tileSize.x, gridSize.y / tileSize.y, 4);
	m_tracer.setRadius(1.0f);
	m_tracer.setFillColor(sf::Color(0, 100, 20, 15));
	m_tracer.setPosition(605, 444);
	
	flowWindowTexture.create(gridSize.x, gridSize.y);
	flowWindow.setSize(sf::Vector2f(gridSize.x, gridSize.y));
	flowWindowTexture.clear(sf::Color(0, 0, 0, 0));

	// Create gradient for and apply to lines (needles)
	sf::Uint8* pixels = new sf::Uint8[400];
	for (int i = 0; i < 100; i++)
	{
		pixels[i * 4 + 0] = 255;
		pixels[i * 4 + 1] = 255 - (i * 2);
		pixels[i * 4 + 2] = 255 - (i * 2);
		pixels[i * 4 + 3] = 55 + i * 2;
	}
	sf::Image image;
	image.create(100, 1, pixels);
	m_gradient.loadFromImage(image);
	m_line.setTexture(&m_gradient);
	delete[] pixels;

	// Clamp angle
	float lowest{ 1.f };
	float highest{ -1.f };
	for (unsigned int i = 0; i < gridSize.x / tileSize.x; i++)
	{
		for (unsigned int j = 0; j < gridSize.y / tileSize.y; j++)
		{
			// this looks wrong.
			float angle = m_simplexData[i + j * (gridSize.x / tileSize.x)] * PI;

			if (angle < lowest) { lowest = angle; }
			if (angle > highest) { highest = angle; }
			angleVector.push_back(angle);
		}
	}

	// Initialize quads to draw the grid
	for (unsigned int i = 0; i < gridSize.x / tileSize.x; i++)
	{
		for (unsigned int j = 0; j < gridSize.y / tileSize.y; j++)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * (gridSize.y / tileSize.y)) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].color = sf::Color(0, 0, 0, 185);
			quad[1].color = sf::Color(0, 60, 0, 185);
			quad[2].color = sf::Color(0, 12, 0, 185);
			quad[3].color = sf::Color(0, 33, 0, 185);
		}
	}
};
void Flow::drawFlow(FlowPreset& fp)
{
	sf::Color initialColor = sf::Color(fp.red, fp.green, fp.blue, fp.alpha);
	const int xPaths{ fp.xCount };
	const int yPaths{ fp.yCount };

	sf::Vector2f returnPos;
	float angle;
	float initialRadius{ 1.0f };
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator

	// Draw Grid
	if (m_drawGrid)
	{
		flowWindowTexture.draw(m_vertices);
		m_drawGrid = false;
	}
	// Draw Compass Needles
	if (m_drawNeedles)
	{
		for (unsigned int j = 0; j < gridSize.y / tileSize.y; j++)
		{
			for (unsigned int i = 0; i < gridSize.x / tileSize.x; i++)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * (gridSize.y / tileSize.y)) * 4];

				angle = angleVector[i + j * (gridSize.x / tileSize.x)];

				const sf::Vector2f quadCenter = sf::Vector2f(quad[2].position.x - (tileSize.x / 2), quad[2].position.y - (tileSize.y / 2));
				m_line.setPosition(quadCenter);
				m_line.setRotation(angle);

				quad = nullptr; // ?
				flowWindowTexture.draw(m_line);
			}
		}
		m_drawNeedles = false;
	}
	// Draw paths
	if (m_drawLines)
	{
		if (fp.ppCounter < fp.plottedPoints)
		{
			for (int iii = 0; iii < yPaths; iii++)
			{
				for (int ii = 0; ii < xPaths; ii++)
				{

					const int startPosX{ static_cast<int>(ii * (gridSize.x / xPaths) + ((gridSize.x / xPaths) / 2)) };
					const int startPosY{ static_cast<int>(iii * (gridSize.y / yPaths) + ((gridSize.y / yPaths) / 2)) };
					m_tracer.setPosition(sf::Vector2f(startPosX, startPosY));
					m_tracer.setFillColor(initialColor);
					m_tracer.setRadius(initialRadius);

					this->m_drawAllLines(fp);
				}
			}
			fp.ppCounter++;
		}
		else
		{
			fp.ppCounter = 0;
			m_drawLines = false;
		}
	}

	if (m_drawGrid || m_drawNeedles || m_drawLines)
	{
		flowWindowTexture.display();
		flowWindow.setTexture(&flowWindowTexture.getTexture());
	}

}

// Private
void Flow::m_applyChanges(FlowPreset& fp)
{
	int id = fp.name;
	switch (id)
	{
	case InProgress:
		currentName = "InProgress";
		fp.red = m_tracer.getFillColor().r + 1.5;
		break;

	case DragonFlame:
		currentName = "DragonFlame";
		// Colour changes
		fp.red = m_tracer.getFillColor().r * 0.999;
		fp.green = m_tracer.getFillColor().g * 0.999;
		fp.blue = m_tracer.getFillColor().b * 1.005;
		fp.alpha = m_tracer.getFillColor().a * 0.999;
		// Radius changes
		m_tracer.setRadius(m_tracer.getRadius() + 0.15f);
		break;

	case CyanRivers:
		currentName = "CyanRivers";
		break;
	default:
		currentName = "untitled";
		break;
	}

	// Common actions
	const sf::Color newColor = sf::Color(
		static_cast<int>(fp.red),
		static_cast<int>(fp.green),
		static_cast<int>(fp.blue),
		static_cast<int>(fp.alpha)
	);
	m_tracer.setFillColor(newColor);
}

void Flow::m_drawAllLines(FlowPreset& fp)
{
	//random distribution
//std::uniform_int_distribution<> distr(0, flow.gridSize.x); // define the range
//int rdmX = distr(gen); // generate numbers
//std::uniform_int_distribution<> distr2(0, flow.gridSize.y); // define the range
//int rdmY = distr(gen);

	for (int i = 0; i < fp.ppCounter; i++)
	{
		m_applyChanges(fp);

		sf::Vector2f pos(m_tracer.getPosition());
		if (pos.x > gridSize.x || pos.y > gridSize.y)
		{
			pos.x = gridSize.x;
			pos.y = gridSize.y;
		}
		const int gridX{ static_cast<int>(floatify(pos.x) / floatify(tileSize.x)) };
		const int gridY{ static_cast<int>(floatify(pos.y) / floatify(tileSize.y)) };
		const float angle = angleVector[gridX + gridY * (gridSize.x / tileSize.x)];

		// Converts the angle to x,y coordinates and moves the tracer
		const float newX = cos(angle * (PI / 180));
		const float newY = sin(angle * (PI / 180));
		m_tracer.move(newX * fp.stepSize, newY * fp.stepSize);
	}
	// Bounds the tracer to the drawing area
	if (m_tracer.getPosition().x < gridSize.x - 1 && m_tracer.getPosition().y < gridSize.y - 1)
	{
		flowWindowTexture.draw(m_tracer);
	}


}
