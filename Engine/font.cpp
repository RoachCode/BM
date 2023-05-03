#pragma once
#include "font.h"
#include <iostream>

/*
bool Font::attachCharTextureToRect(char input)
{
	textRect.setSize(sf::Vector2f(6, 8));
	switch (input)
	{
	case 'A':
		textRect.setTexture(&A);
		return true;
		break;
	case 'B':
		textRect.setTexture(&B);
		return true;
		break;
	case 'C':
		textRect.setTexture(&C);
		return true;
		break;
	case 'D':
		textRect.setTexture(&D);
		return true;
		break;
	case 'E':
		textRect.setTexture(&E);
		return true;
		break;
	case 'F':
		textRect.setTexture(&F);
		return true;
		break;
	case 'G':
		textRect.setTexture(&G);
		return true;
		break;
	case 'H':
		textRect.setTexture(&H);
		return true;
		break;
	case 'I':
		textRect.setTexture(&I);
		return true;
		break;
	case 'J':
		textRect.setTexture(&J);
		return true;
		break;
	case 'K':
		textRect.setTexture(&K);
		return true;
		break;
	case 'L':
		textRect.setTexture(&L);
		return true;
		break;
	case 'M':
		textRect.setTexture(&M);
		return true;
		break;
	case 'N':
		textRect.setTexture(&N);
		return true;
		break;
	case 'O':
		textRect.setTexture(&O);
		return true;
		break;
	case 'P':
		textRect.setTexture(&P);
		return true;
		break;
	case 'Q':
		textRect.setTexture(&Q);
		return true;
		break;
	case 'R':
		textRect.setTexture(&R);
		return true;
		break;
	case 'S':
		textRect.setTexture(&S);
		return true;
		break;
	case 'T':
		textRect.setTexture(&T);
		return true;
		break;
	case 'U':
		textRect.setTexture(&U);
		return true;
		break;
	case 'V':
		textRect.setTexture(&V);
		return true;
		break;
	case 'W':
		textRect.setTexture(&W);
		return true;
		break;
	case 'X':
		textRect.setTexture(&X);
		return true;
		break;
	case 'Y':
		textRect.setTexture(&Y);
		return true;
		break;
	case 'Z':
		textRect.setTexture(&Z);
		return true;
		break;
	case ' ':
		textRect.setTexture(&sp);
		return true;
		break;
	case '0':
		textRect.setTexture(&zero);
		return true;
		break;
	case '1':
		textRect.setTexture(&one);
		return true;
		break;
	case '2':
		textRect.setTexture(&two);
		return true;
		break;
	case '3':
		textRect.setTexture(&three);
		return true;
		break;
	case '4':
		textRect.setTexture(&four);
		return true;
		break;
	case '5':
		textRect.setTexture(&five);
		return true;
		break;
	case '6':
		textRect.setTexture(&six);
		return true;
		break;
	case '7':
		textRect.setTexture(&seven);
		return true;
		break;
	case '8':
		textRect.setTexture(&eight);
		return true;
		break;
	case '9':
		textRect.setTexture(&nine);
		return true;
		break;
	default:
		//std::cout << "fallthrough";
		return false;
		break;
	}
}

void Font::setPos(sf::Vector2f newPos)
{
	textRect.setPosition(newPos);
}

sf::Vector2f Font::getPos()
{
	return textRect.getPosition();
}

void Font::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	textRed = red;
	textGreen = green;
	textBlue = blue;
	createFontTextures();
}

void Font::move(sf::Vector2f offset)
{
	textRect.move(offset);
}

sf::RectangleShape Font::getRect()
{
	return textRect;
}

void Font::setStartPos(sf::Vector2f startPosition)
{
	startPos = startPosition;
}

sf::Vector2f Font::getStartPos()
{
	return startPos;
}
*/
//////////////////////////////////////////////////////////////

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

void Font2::setColor(sf::Color colorIn)
{
	textRed = colorIn.r;
	textGreen = colorIn.g;
	textBlue = colorIn.b;
	const int imagePixelW = fontImage.getSize().x;
	const int imagePixelH = fontImage.getSize().y;
	for (int i = 0; i < imagePixelW; i++)
	{
		for (int j = 0; j < imagePixelH; j++)
		{
			sf::Color color = fontImage.getPixel(i, j);
			if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
			{
				fontImage.setPixel(i, j, sf::Color(textRed, textGreen, textBlue));
			}
		}
	}
	fontTexture.loadFromImage(fontImage);
	charSprite.setTexture(fontTexture);
}

enum CharRects
{
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	sp, zero, one, two, three, four, five, six, seven, eight, nine, ten
};

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