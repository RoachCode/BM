#pragma once
#include <SFML/Graphics.hpp>
#include "particles.h"
#include "OpenSimplexNoise.h"

class Flow
{
public:
	std::string currentName;
	unsigned int width;
	unsigned int height;
	sf::VertexArray m_vertices;
	sf::Image image;
	sf::Texture gradient;
	sf::Vector2u tileSize;
	sf::Vector2u gridSize;
	sf::RectangleShape line;
	std::vector<float> angleVector;
	sf::CircleShape tracer;

	float simplexSizeX;
	float simplexSizeY;
	std::deque<sf::Uint8> simplexData;
	int simplexOctaves;
	std::vector<float> xyValues;
	std::vector<int> tempContainer;
	Flow()
	{

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
			pixels[i * 4 + 3] = 255;
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

				quad[0].color = sf::Color(0, 255, 0, 35);
				quad[1].color = sf::Color(50, 0, 0, 35);
				quad[2].color = sf::Color(222, 155, 0, 35);
				quad[3].color = sf::Color(0, 0, 0, 35);
			}
		}
	}

	void createSimplexValues(int x, int y)
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

	void initSimplex(float sizeX, float sizeY, int octaves)
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
	void normalizeRGB()
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
};



//float red;
//float green;
//float blue;
//float alpha - transparency;
//int plottedPoints - how many points to plot before moving to the next xCount; ie, how long the "line" that gets drawn is
//float stepSize - how far to move between calls to draw; (fineness of line - big numbers lead to dotted lines)
//int xCount - number of start points to create, wide
//int yCount - number of start points to create, high
//bool granularDisplay - slow display but shows more frames
class FlowPreset
{
public:
	int name;
	float red;
	float green;
	float blue;
	float alpha;

	int plottedPoints;
	float stepSize;

	int xCount;
	int yCount;
	bool granularDisplay;

	FlowPreset() : name(-1), red(0), green(0), blue(255), alpha(255), plottedPoints(20), stepSize(100), xCount(2), yCount(2), granularDisplay(false) {};

	FlowPreset(int n, float r, float g, float b, float a, int pp, float ss, int xcount, int ycount, bool gDisp) :
		name(n),
		red(r),
		green(g),
		blue(b),
		alpha(a),
		plottedPoints(pp),
		stepSize(ss),
		xCount(xcount),
		yCount(ycount),
		granularDisplay(gDisp)
	{
		//
	};

	void applyChanges(Flow& fl)
	{
		int id = name;
		switch (id)
		{
		case InProgress:
			fl.currentName = "InProgress";
			//////////////////////////////////////////////////////////////////////////////
			//fl.tracer.setRadius(1.0f); // default 1.0
			//////////////////////////////////////////////////////////////////////////////
			break;
		case DragonFlame:
			fl.currentName = "DragonFlame";
			// Colour changes
			red = fl.tracer.getFillColor().r - 0.12;
			green = fl.tracer.getFillColor().g - 0.12;
			blue = fl.tracer.getFillColor().b + 0.5;
			alpha = fl.tracer.getFillColor().a * 0.7;

			// Radius changes
			fl.tracer.setRadius(fl.tracer.getRadius() + 2.5f);
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
};

