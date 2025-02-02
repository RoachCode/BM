#pragma once
#include <SFML/Graphics.hpp>

#include <deque>
#include "constExpressions.h"
#include "maps.h"
#include "noise.h"
#include "imageHandler.h"

class Water : public ImageHandler
{
public:
	std::vector<bool> westKagarWater;
	sf::Clock clock;
	Noise noise;
	sf::Image waterAnimationFrames;

	int animationDepth{};
	int animationTime{};
	int width;
	int height;

	void createWaterTileMapArray()
	{
		if (!westKagarWater.size())
		{
			for (size_t i = 0; i < tileMapE.masterTile.size(); i++)
			{
				if (tileMapE.masterTile[i] == 89 || tileMapE.masterTile[i] == 90)
				{
					westKagarWater.push_back(1);
				}
				else
				{
					westKagarWater.push_back(0);
				}
			}
		}
	}

	Water()
	{
		noise.m_simplexSizeX = 32;
		noise.m_simplexSizeY = 32;
		width = noise.m_simplexSizeX;
		height = noise.m_simplexSizeY;

		noise.noise.setSize(pairF(width, height));
		noise.isWater = true;
		animationDepth = 300;
		noise.stepSize = 0.03f;
		noise.startOctave = 1;

		waterAnimationFrames.create(width * animationDepth, height);
		//noise.m_initSimplex(width, height, 2);

		createWaterTileMapArray();//
		createWaterAnimations();

	}


	void update()
	{
		sf::Time elapsed = clock.getElapsedTime();
		int elapsedTime{ elapsed.asMilliseconds() / 100 };
		if (animationTime == elapsedTime) { return; }
		if (noise.reverse && elapsedTime == 0) { return; }
		animationTime = elapsedTime;

		if (!noise.reverse)
		{
			if (animationTime <= animationDepth - 1)
			{
				noise.noise.setTextureRect(sf::IntRect(width * animationTime, 0, width, height));
			}
			else
			{
				noise.reverse = true;
				clock.restart();
				animationTime = 1;
			}
		}
		if (noise.reverse)
		{
			if (animationTime <= animationDepth)
			{
				noise.noise.setTextureRect(sf::IntRect((animationDepth - animationTime) * width, 0, width, height));
			}
			else
			{
				noise.reverse = false;
				clock.restart();
				animationTime = 0;
			}
		}
	}

	void createWaterAnimations()
	{
		for (int i = 0; i < animationDepth; i++)
		{
			noise.qdMod = noise.stepSize * i;
			noise.m_initSimplex(width, height, 4);

			const int x{ intify(noise.m_simplexSizeX) };
			const int y{ intify(noise.m_simplexSizeY) };
			noise.noise.setSize(pairF(x, y));

			sf::Uint8* pixels = new sf::Uint8[width * height * 4];
			for (int j = 0; j < width * height; j++)
			{
				// invert
				noise.m_simplexData[j] = 255 - noise.m_simplexData[j];
				// clamp
				pixels[j * 4 + 0] = noise.m_simplexData[j] / 5;
				pixels[j * 4 + 1] = noise.m_simplexData[j] / 3;
				pixels[j * 4 + 2] = noise.m_simplexData[j] / 2;
				pixels[j * 4 + 3] = noise.m_simplexData[j] / 1.75;

			}
			sf::Image image;
			image.create(width, height, pixels);
			delete[] pixels;
			waterAnimationFrames.copy(image, i * width, 0);
		}

		//
		//sf::Image image;
		//image.create(width, height);
		//waterAnimationFrames.copy(image, 0, 0);
		//
		noise.noiseTexture.create(waterAnimationFrames.getSize().x, height);
		noise.noiseTexture.loadFromImage(waterAnimationFrames);
		noise.noise.setTexture(&noise.noiseTexture);
	}
};
