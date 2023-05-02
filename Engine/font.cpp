#pragma once
#include "font.h"
#include <iostream>

void Font::createFontTextures()
{
	const int pixPerChar{ 48 };
	for (int i = 0; i < characterTextures.size(); i++)
	{
		characterTextures[i]->create(6, 8);
		uint8_t* pixels = new uint8_t[pixPerChar * 4];

		for (int j = 0; j < pixPerChar; j++)
		{
			if (AthroughTildeData[j + i * pixPerChar] == true)
			{
				pixels[(j * 4) + 0] = textRed;
				pixels[(j * 4) + 1] = textGreen;
				pixels[(j * 4) + 2] = textBlue;
				pixels[(j * 4) + 3] = 255;
			}
			else
			{
				pixels[(j * 4) + 0] = 0;
				pixels[(j * 4) + 1] = 0;
				pixels[(j * 4) + 2] = 0;
				pixels[(j * 4) + 3] = 0;
			}
		}
		characterTextures[i]->update(pixels);
		delete[] pixels;
	}
}

Font::Font()
{
	startPos = sf::Vector2f(50, 50);
	createFontTextures();
}

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