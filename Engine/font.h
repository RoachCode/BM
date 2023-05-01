#pragma once
#include "filesys.h"
#include <SFML/Graphics.hpp>

/*
	uint8_t a[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
*/

class Font
{
private:
	// get colour from some variable, and apply it when converting to rgb values for texture
	std::vector<bool> Adata =
	{
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
	};

public:
	sf::Texture texture;
	sf::RectangleShape A;
	uint8_t textRed{ 0 };
	uint8_t textGreen{ 0 };
	uint8_t textBlue{ 0 };
	Font()
	{
		textureUpdate();
	}

    void textureUpdate()
    {
		A.setSize(sf::Vector2f(6, 8));
		A.setPosition(sf::Vector2f(6, 8));
        texture.create(6, 8);
        sf::Uint8* pixels = new sf::Uint8[8 * 6 * 4];

        for (int i = 0; i < 6 * 8; i ++)
        {
			if (Adata[i])
			{
				pixels[i * 4] = textRed;
				pixels[i * 4 + 1] = textGreen;
				pixels[i * 4 + 2] = textBlue;
				pixels[i * 4 + 3] = 255;
			}
			else
			{
				pixels[i * 4] = 0;
				pixels[i * 4 + 1] = 0;
				pixels[i * 4 + 2] = 0;
				pixels[i * 4 + 3] = 0;
			}

        }
        texture.update(pixels);
        A.setTexture(&texture);
        delete[] pixels;
    }

};