#pragma once
#include <SFML/Graphics.hpp>
#include "OpenSimplexNoise.h"
#include <deque>
#include "constExpressions.h"



extern class Water
{
public:
	std::vector<bool> westKagarWater = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	};
	sf::Clock clock;
	std::vector<float>xyValues;
	std::vector<float> angleVector;
	std::vector<int> tempContainer;
	float simplexSizeX;
	float simplexSizeY;
	std::deque<sf::Uint8> simplexData;
	int simplexOctaves;
	int width{ 32 };
	int height{ 32 };
	sf::RectangleShape waterTile;
	sf::Texture waterTexture1;
	bool reverse{ false };
	int animationDepth{};
	float stepSize{};

	void createSimplexValues(int x, int y, float bullshitModifier)
	{
		xyValues.clear();

			int octave{ 1 };
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
						float bs = bullshitModifier;

						// clamping to [0, 1]
						float dx = x2 - x1;
						float dy = y2 - y1;


						// 4d noise. two orthogonal 3d cylinders. Loops continuously along x and y dimensions.
						//float modX = x1 + cos(s * 2 * PI) * dx / (2 * PI / octave);
						//float modY = y1 + cos(t * 2 * PI) * dy / (2 * PI / octave);
						//float modZ = x1 + sin(s * 2 * PI) * dx / (2 * PI / octave);
						//float modW = y1 + sin(t * 2 * PI) * dy / (2 * PI / octave);


						float modX = x1 + bs + cos(s * 2 * PI) * dx / (2 * PI / octave);
						float modY = y1 - bs + cos(t * 2 * PI) * dy / (2 * PI / octave);
						float modZ = x1 + bs + sin(s * 2 * PI) * dx / (2 * PI / octave);
						float modW = y1 - bs + sin(t * 2 * PI) * dy / (2 * PI / octave);

						xyValues.push_back(modX);
						xyValues.push_back(modY);
						xyValues.push_back(modZ);
						xyValues.push_back(modW);

					}
				}
			}
			octave = 1;
		
	}
	void initSimplex(float sizeX, float sizeY, int octaves, float bullshitMod)
	{
		OpenSimplexNoise::Noise simplex(494358);
		simplexOctaves = octaves;
		simplexSizeX = sizeX;
		simplexSizeY = sizeY;

		const float x{ sizeX };
		const float y{ sizeY };


		createSimplexValues(x, y, bullshitMod);
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


			noise *= (254.999 / simplexOctaves);
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

			//optional clamping for water
			tempContainer[i] = tempContainer[i] / 25;
			tempContainer[i] = tempContainer[i] * 25;
			if (tempContainer[i] > 150)
			{
				tempContainer[i] /= 5;
			}
			if (tempContainer[i] < 120)
			{
				tempContainer[i] *= 5;
			}
			//std::cout << noiseInt << '\n';
			sf::Uint8 noiseUint = sf::Uint8(tempContainer[i]);
			simplexData.push_back(noiseUint);
		}
	}

	Water()
	{
		// use keys t and y to cycle through the current 2 textures for water.
		width = 32;
		height = 32;
		waterTile.setSize(sf::Vector2f(width, height));

		animationDepth = 300;
		stepSize = 0.03f;

		initSimplex(width, height, 2, 0);
		createImage();
	}

	void update(sf::Time elapsed)
	{
		int animTime = elapsed.asMilliseconds() / 100;

		if (animTime >= animationDepth)
		{
			reverse = true;
			clock.restart();
			animTime = 0;
		}
		if (reverse)
		{
			initSimplex(width, height, 4, stepSize * (animationDepth - animTime));
			if (animTime >= animationDepth - 1)
			{
				reverse = false;
				clock.restart();
				animTime = 0;
			}
		}
		else
		{
			initSimplex(width, height, 4, stepSize * animTime);
		}

		createImage();

	}

	void createImage()
	{
		sf::Uint8* pixels = new sf::Uint8[width * height * 4];
		for (int i = 0; i < width * height; i++)
		{
			// clamp
			simplexData[i] = 255 - simplexData[i];

			pixels[i * 4 + 0] = simplexData[i] / 5;
			pixels[i * 4 + 1] = simplexData[i] / 3;
			pixels[i * 4 + 2] = simplexData[i] / 2;
			pixels[i * 4 + 3] = simplexData[i] / 2;

		}
		sf::Image image;
		image.create(width, height, pixels);
		delete[] pixels;
		waterTexture1.create(width, height);
		waterTexture1.loadFromImage(image);
		waterTile.setTexture(&waterTexture1);

	}

};
