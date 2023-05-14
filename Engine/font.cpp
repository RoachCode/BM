#pragma once
#include "font.h"
#include <iostream>

Font2::Font2()
{
	createFontImageAndTexture();
}

void Font2::createFontImageAndTexture()
{
	const int pixPerChar{ 48 };	
	fontTexture.create((AthroughTildeData.size() / pixPerChar) * 6, 8);
	fontImage.create((AthroughTildeData.size() / pixPerChar) * 6, 8);
	for (int i = 0; i < AthroughTildeData.size() / pixPerChar; i++)
	{
		sf::Uint8* pixels = new sf::Uint8[pixPerChar * 4];

		for (int j = 0; j < pixPerChar; j++)
		{
			if (AthroughTildeData[j + i * pixPerChar] == true)
			{
				pixels[(j * 4) + 0] = textRed;
				pixels[(j * 4) + 1] = textGreen;
				pixels[(j * 4) + 2] = textBlue;
				pixels[(j * 4) + 3] = sf::Uint8(255);
			}
			else
			{
				pixels[(j * 4) + 0] = alphaKey.r;
				pixels[(j * 4) + 1] = alphaKey.g;
				pixels[(j * 4) + 2] = alphaKey.b;
				pixels[(j * 4) + 3] = sf::Uint8(0);
			}
		}
		sf::Image charImage;
		charImage.create(6, 8, pixels);
		fontImage.copy(charImage, i * 6, 0);
		delete[] pixels;
		fontTexture.loadFromImage(fontImage);
		charSprite.setTexture(fontTexture);
	}
}

void Font2::setColor(sf::Color colorIn, bool ignoreReassignment)
{
	if (!ignoreReassignment)
	{
		textRed = sf::Uint8(colorIn.r);
		textGreen = sf::Uint8(colorIn.g);
		textBlue = sf::Uint8(colorIn.b);
	}
	resetImage(colorIn);
}

void Font2::resetImage(sf::Color colorIn2)
{
	const int imagePixelW = fontImage.getSize().x;
	const int imagePixelH = fontImage.getSize().y;
	for (int i = 0; i < imagePixelW; i++)
	{
		for (int j = 0; j < imagePixelH; j++)
		{
			sf::Color color = fontImage.getPixel(i, j);
			if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
			{
				fontImage.setPixel(i, j, colorIn2);
			}
		}
	}
	fontTexture.loadFromImage(fontImage);
	charSprite.setScale(sf::Vector2f(1, 1)); // ? not sure if needed.
	charSprite.setTexture(fontTexture);
}

int Font2::getRectOffset(char input)
{
	switch (input)
	{
	case 'A': return 0;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	case 'G': return 6;
	case 'H': return 7;
	case 'I': return 8;
	case 'J': return 9;
	case 'K': return 10;
	case 'L': return 11;
	case 'M': return 12;
	case 'N': return 13;
	case 'O': return 14;
	case 'P': return 15;
	case 'Q': return 16;
	case 'R': return 17;
	case 'S': return 18;
	case 'T': return 19;
	case 'U': return 20;
	case 'V': return 21;
	case 'W': return 22;
	case 'X': return 23;
	case 'Y': return 24;
	case 'Z': return 25;
	case ' ': return 26;
	case '0': return 27;
	case '1': return 28;
	case '2': return 29;
	case '3': return 30;
	case '4': return 31;
	case '5': return 32;
	case '6': return 33;
	case '7': return 34;
	case '8': return 35;
	case '9': return 36;
	default:
		std::cout << "character missing ";
		return -1;
	}
};

bool Font2::attachCharImageSubRectToSprite(char input)
{
	int offset{ getRectOffset(input) };
	if (offset == -1) { return false; }
	charSprite.setScale(sf::Vector2f(1, 1));
	charSprite.setTextureRect(sf::IntRect(offset * 6, 0, 6, 8));
	return true;
}

//void Font2::drawText(std::string string)

void Font2::move(sf::Vector2f offset)
{
	charSprite.move(offset);
}

sf::Vector2f Font2::getPos() { return charSprite.getPosition(); }
void Font2::setPos(sf::Vector2f newPos) { charSprite.setPosition(newPos); }
sf::Vector2f Font2::getStartPos() { return startPos; }
void Font2::setStartPos(sf::Vector2f newPos) { startPos = newPos; }