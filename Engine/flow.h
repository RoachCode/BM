#pragma once
#include <SFML/Graphics.hpp>
#include "particles.h"
#include "OpenSimplexNoise.h"

class Flow
{
public:
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

		width = sf::VideoMode::getDesktopMode().width / 2; // because we're zoomed in right now...
		height = sf::VideoMode::getDesktopMode().height / 2;
		m_vertices.setPrimitiveType(sf::Quads);
		const int gridFactor{ 100 };
		tileSize = sf::Vector2u(width / gridFactor, height / gridFactor); // defines the density of the grid
		gridSize = sf::Vector2u(static_cast<unsigned int>(tileSize.x) * gridFactor, static_cast<unsigned int>(tileSize.y) * gridFactor);
		m_vertices.resize(gridSize.x * gridSize.y * 4);
		line.setSize(sf::Vector2f(height / 50 / 2, 0.5));

		initSimplex(gridSize.x / tileSize.x, gridSize.y / tileSize.y, 4);

		tracer.setRadius(0.5f);
		tracer.setFillColor(sf::Color(0, 100, 100, 25));
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

				float angle = simplexData[i + j * (gridSize.x / tileSize.x)] * PI;

				if (angle < lowest) { lowest = angle; }
				if (angle > highest) { highest = angle; }
				angleVector.push_back(angle);
			}
		}
		//std::cout << "Lowest: " << lowest << "     Highest: " << highest << '\n';
	}

	void createSimplexValues(int x, int y)
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


			noise *= (255.999 / simplexOctaves);
			// need to correct for the noise having 1.5x the value it should, for some reason.
			noise = (noise * 2) / 3;
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