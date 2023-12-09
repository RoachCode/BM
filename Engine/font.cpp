#pragma once
#include "font.h"
#include <iostream>

Font2::Font2()
{
	//setColor(sf::Color(255, 120, 10));
	createFontImageAndTexture();
}

void Font2::setCharTextureToSprite(int pixPerChar, int charCount, int width, sf::Image &image, sf::Texture &texture)
{
	const int height{ 8 };
	for (int i = 0; i < charCount; i++)
	{
		sf::Uint8* pixels = new sf::Uint8[pixPerChar * 4];

		for (int j = 0; j < pixPerChar; j++)
		{
			// Picks from correct image array based on width of character
			switch (width)
			{
			case 2:
				if (punctuationChars[j + i * pixPerChar] == true)
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
				break;
			case 6:
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
				break;
			case 8:
				if (specialChars[j + i * pixPerChar] == true)
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
				break;
			default:
				break;
			};
		}
		sf::Image charImage;
		charImage.create(width, height, pixels);
		delete[] pixels;
		image.copy(charImage, i * width, 0);

		texture.create(width, height);
		texture.loadFromImage(image);

		charSprite.setTexture(texture);
	}
}

void Font2::createFontImageAndTexture(sf::Color color)
{
	const int pixPerChar1{ 48 };
	const int pixPerChar2{ 64 };
	const int pixPerChar3{ 16 };

	const int charCount1{ 68 };
	const int charCount2{ 6 };
	const int charCount3{ 3 };

	const int w1{ 6 };
	const int w2{ 8 };
	const int w3{ 2 };

	if (!fontTexture.create(charCount1 * w1, 8)) { std::cout << "failed - fontTexture.create()" << '\n'; }
	if (!fontSpecialTexture.create(charCount2 * w2, 8)) { std::cout << "failed - fontSpecialTexture.create()" << '\n'; }
	if (!fontPunctuationTexture.create(charCount3 * w3, 8)) { std::cout << "failed - fontPunctuationTexture.create()" << '\n'; }

	fontImage.create(charCount1 * w1, 8);
	fontSpecialImage.create(charCount2 * w2, 8);
	fontPunctuationImage.create(charCount3 * w3, 8);

	setColor(color);

	setCharTextureToSprite(pixPerChar1, charCount1, w1, fontImage, fontTexture);
	setCharTextureToSprite(pixPerChar2, charCount2, w2, fontSpecialImage, fontSpecialTexture);
	setCharTextureToSprite(pixPerChar3, charCount3, w3, fontPunctuationImage, fontPunctuationTexture);

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
	case 'a': return 37;
	case 'b': return 38;
	case 'c': return 39;
	case 'd': return 40;
	case 'e': return 41;
	case 'f': return 42;
	case 'g': return 43;
	case 'h': return 44;
	case 'i': return 45;
	case 'j': return 46;
	case 'k': return 47;
	case 'l': return 48;
	case 'm': return 49;
	case 'n': return 50;
	case 'o': return 51;
	case 'p': return 52;
	case 'q': return 53;
	case 'r': return 54;
	case 's': return 55;
	case 't': return 56;
	case 'u': return 57;
	case 'v': return 58;
	case 'w': return 59;
	case 'x': return 60;
	case 'y': return 61;
	case 'z': return 62;
	case '?': return 63;
	case '!': return 64;
	case '@': return 65;
	case '#': return 66;
	case '$': return 67;
	case '~': return 68;
	case '^': return 69;//
	case '|': return 70;
	case '_': return 71;
	case '<': return 72;
	case '=': return 73;
	case '{': return 74;
	case ':': return 75;//
	case '.': return 76;
	case ',': return 77;
	default:
		std::cout << "character missing: " << input << '\n';
		return -1;
	}
};
bool Font2::attachCharImageSubRectToSprite(char input)
{
	int offset{ getRectOffset(input) };
	if (offset == -1) { return false; }
	if (offset == 77) { addon.y = 1; } // comma
	if (offset == 43 || offset == 46 || offset == 52 || offset == 53 || offset == 61) { addon.y = 2; } // all the other low letters
	//if (offset == 48) { addon.x = -1; }

	if (offset < 69)
	{
		charSprite.setTexture(fontTexture);
		charSprite.setTextureRect(sf::IntRect(offset * 6, 0, 6, 8));
		return true;
	}
	else if (offset < 75)
	{
		charSprite.setTexture(fontSpecialTexture);
		charSprite.setTextureRect(sf::IntRect((offset - 69) * 8, 0, 8, 8));
		return true;
	}
	else if (offset < 78)
	{
		charSprite.setTexture(fontPunctuationTexture);
		charSprite.setTextureRect(sf::IntRect((offset - 75) * 2, 0, 2, 8));
		return true;
	}
	return false;
}

void Font2::setColor(sf::Color colorIn, bool ignoreReassign)
{
	if (!ignoreReassign)
	{
		textRed = sf::Uint8(colorIn.r);
		textGreen = sf::Uint8(colorIn.g);
		textBlue = sf::Uint8(colorIn.b);
	}
	int imagePixelW = fontImage.getSize().x;
	int imagePixelH = fontImage.getSize().y;
	for (int i = 0; i < imagePixelW; i++)
	{
		for (int j = 0; j < imagePixelH; j++)
		{
			sf::Color color = fontImage.getPixel(i, j);
			if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
			{
				fontImage.setPixel(i, j, colorIn);
			}
		}
	}
	fontTexture.loadFromImage(fontImage);
//
	imagePixelW = fontSpecialImage.getSize().x;
	imagePixelH = fontSpecialImage.getSize().y;
	for (int i = 0; i < imagePixelW; i++)
	{
		for (int j = 0; j < imagePixelH; j++)
		{
			sf::Color color = fontSpecialImage.getPixel(i, j);
			if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
			{
				fontSpecialImage.setPixel(i, j, colorIn);
			}
		}
	}
	fontSpecialTexture.loadFromImage(fontSpecialImage);
//
	imagePixelW = fontPunctuationImage.getSize().x;
	imagePixelH = fontPunctuationImage.getSize().y;
	for (int i = 0; i < imagePixelW; i++)
	{
		for (int j = 0; j < imagePixelH; j++)
		{
			sf::Color color = fontPunctuationImage.getPixel(i, j);
			if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
			{
				fontPunctuationImage.setPixel(i, j, colorIn);
			}
		}
	}
	fontPunctuationTexture.loadFromImage(fontPunctuationImage);

	const int charWidth{ intify(charSprite.getLocalBounds().width) };
	switch (charWidth)
	{
	case 2:
		charSprite.setTexture(fontPunctuationTexture);
		break;
	case 6:
		charSprite.setTexture(fontTexture);
		break;
	case 8:
		charSprite.setTexture(fontSpecialTexture);
		break;
	default:
		break;
	};
}
void Font2::move(sf::Vector2f offset)
{
	charSprite.move(offset);
}
sf::Vector2f Font2::getPos() { return charSprite.getPosition(); }
void Font2::setPos(sf::Vector2f newPos) { charSprite.setPosition(newPos); }
sf::Vector2f Font2::getStartPos() { return startPos; }
void Font2::setStartPos(sf::Vector2f newPos) { startPos = newPos; }