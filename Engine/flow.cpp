#pragma once
#include "flow.h"

Flow::Flow()
{
	drawGrid = false;
	drawNeedles = false;
	drawLines = true;

	width = sf::VideoMode::getDesktopMode().width;
	height = sf::VideoMode::getDesktopMode().height;
	m_vertices.setPrimitiveType(sf::Quads);
	const int gridFactor{ 100 };
	tileSize = sf::Vector2u(width / gridFactor, height / gridFactor); // defines the density of the grid
	gridSize = sf::Vector2u(static_cast<unsigned int>(tileSize.x) * gridFactor, static_cast<unsigned int>(tileSize.y) * gridFactor);
	m_vertices.resize(gridSize.x * gridSize.y * 4);
	line.setSize(sf::Vector2f(height / 50 / 2, 1));

	initSimplex(gridSize.x / tileSize.x, gridSize.y / tileSize.y, 4);

	tracer.setRadius(1.0f);
	tracer.setFillColor(sf::Color(0, 100, 20, 15));
	tracer.setPosition(605, 444);

	sf::Uint8* pixels = new sf::Uint8[400];
	for (int i = 0; i < 100; i++)
	{
		pixels[i * 4 + 0] = 255;
		pixels[i * 4 + 1] = 255 - (i * 2);
		pixels[i * 4 + 2] = 255 - (i * 2);
		pixels[i * 4 + 3] = 55 + i * 2;
	}

	image.create(100, 1, pixels);
	gradient.loadFromImage(image);
	line.setTexture(&gradient);
	delete[] pixels;
	float lowest{ 1.f };
	float highest{ -1.f };
	for (unsigned int i = 0; i < gridSize.x / tileSize.x; i++)
	{
		for (unsigned int j = 0; j < gridSize.y / tileSize.y; j++)
		{
			// this looks wrong.
			float angle = simplexData[i + j * (gridSize.x / tileSize.x)] * PI;

			if (angle < lowest) { lowest = angle; }
			if (angle > highest) { highest = angle; }
			angleVector.push_back(angle);
		}
	}
	//std::cout << "Lowest: " << lowest << "     Highest: " << highest << '\n';

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

void Flow::createSimplexValues(int x, int y)
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

				xyValues.push_back(modX);
				xyValues.push_back(modY);
				xyValues.push_back(modZ);
				xyValues.push_back(modW);
			}
		}
	}
	octave = 8;
}
void Flow::initSimplex(float sizeX, float sizeY, int octaves)
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


		noise *= (255.999 / simplexOctaves); // overflow???
		int noiseInt = static_cast<int>(noise);
		tempContainer.push_back(noiseInt);

	}
	normalizeRGB();

}
void Flow::normalizeRGB()
{
	int lowest{ 0 };
	int highest{ 0 };
	for (int i = 0; i < tempContainer.size(); i++)
	{

		if (tempContainer[i] < lowest) { lowest = tempContainer[i]; }
		if (tempContainer[i] > highest) { highest = tempContainer[i]; }
	}
	//std::cout << "lowest: " << lowest << "     Highest: " << highest << '\n';
	simplexData.clear();
	for (int i = 0; i < tempContainer.size(); i++)
	{
		tempContainer[i] += abs(lowest);
		if (tempContainer[i] > 255) { tempContainer[i] = 255; }

		//std::cout << noiseInt << '\n';
		sf::Uint8 noiseUint = sf::Uint8(tempContainer[i]);
		simplexData.push_back(noiseUint);
	}
}

bool Flow::queryDrawGrid()
{
	return drawGrid;
}
bool Flow::queryDrawNeedles()
{
	return drawNeedles;
}
bool Flow::queryDrawLines()
{
	return drawLines;
}

void Flow::toggleDrawGrid()
{
	drawGrid = !drawGrid;
}
void Flow::toggleDrawNeedles()
{
	drawNeedles = !drawNeedles;
}
void Flow::toggleDrawLines()
{
	drawLines = !drawLines;
}
void Flow::toggleDrawGrid(bool update)
{
	drawGrid = update;
}
void Flow::toggleDrawNeedles(bool update)
{
	drawNeedles = update;
}
void Flow::toggleDrawLines(bool update)
{
	drawLines = update;
}

void Flow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}








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

void FlowPreset::applyChanges(Flow& fl)
{
	int id = name;
	switch (id)
	{
	case InProgress:
		fl.currentName = "InProgress";
		//////////////////////////////////////////////////////////////////////////////
		red = fl.tracer.getFillColor().r + 1.5;
		//////////////////////////////////////////////////////////////////////////////
		break;
	case DragonFlame:
		fl.currentName = "DragonFlame";
		// Colour changes
		red = fl.tracer.getFillColor().r * 0.999;
		green = fl.tracer.getFillColor().g * 0.999;
		blue = fl.tracer.getFillColor().b * 1.005;
		alpha = fl.tracer.getFillColor().a * 0.999;

		// Radius changes
		fl.tracer.setRadius(fl.tracer.getRadius() + 0.15f);
		break;
	case CyanRivers:
		fl.currentName = "CyanRivers";
		break;
	default:
		fl.currentName = "untitled";
		break;
	}


	// Common actions
	const sf::Color newColor = sf::Color(
		static_cast<int>(red),
		static_cast<int>(green),
		static_cast<int>(blue),
		static_cast<int>(alpha)
	);
	fl.tracer.setFillColor(newColor);
}


