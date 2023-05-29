#pragma once
#include <SFML/Graphics.hpp>

#include <deque>
#include "constExpressions.h"
#include "maps.h"
#include "noise.h"

extern class Water : public Noise
{
public:
	std::vector<bool> westKagarWater;
	sf::Clock clock;

	int width{ 32 };
	int height{ 32 };
	sf::RectangleShape waterTile;
	sf::Texture waterTexture1;


	Water()
	{
		Noise::isWater = true;
		width = 32;
		height = 32;
		waterTile.setSize(sf::Vector2f(width, height));

		animationDepth = 300;
		stepSize = 0.03f;

		Noise::startOctave = 1;
		Noise::m_initSimplex(width, height, 2);
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
			qdMod = stepSize * (animationDepth - animTime);
			m_initSimplex(width, height, 4);
			if (animTime >= animationDepth - 1)
			{
				reverse = false;
				clock.restart();
				animTime = 0;
			}
		}
		else
		{
			qdMod = stepSize * animTime;
			m_initSimplex(width, height, 4);
		}

		createImage();

	}

	void createImage()
	{
		sf::Uint8* pixels = new sf::Uint8[width * height * 4];
		for (int i = 0; i < width * height; i++)
		{
			// clamp
			m_simplexData[i] = 255 - m_simplexData[i];

			pixels[i * 4 + 0] = m_simplexData[i] / 5;
			pixels[i * 4 + 1] = m_simplexData[i] / 3;
			pixels[i * 4 + 2] = m_simplexData[i] / 2;
			pixels[i * 4 + 3] = m_simplexData[i] / 1.75;

		}
		sf::Image image;
		image.create(width, height, pixels);
		delete[] pixels;
		waterTexture1.create(width, height);
		waterTexture1.loadFromImage(image);
		waterTile.setTexture(&waterTexture1);

	}
};
