#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern class Font
{
private:
	// the first 69 cgaracters can fit in this format
	std::vector<bool> AthroughTildeData =
	{
		// A
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// B
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,

		// C
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,

		// D
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,

		// E
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,

		// F
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,

		// G
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// H
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// I
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,

		// J
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// K
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// L
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,

		// M
		1, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// N
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// O
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// P
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,

		// Q
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 1,

		// R
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// S
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// T
		1, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,

		// U
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// V
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 1, 0,
		0, 0, 1, 1, 0, 0,

		// W
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 0,

		// X
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// Y
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,

		// Z
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,

		// sp
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

	};

	sf::Texture A;
	sf::Texture B;
	sf::Texture C;
	sf::Texture D;
	sf::Texture E;
	sf::Texture F;
	sf::Texture G;
	sf::Texture H;
	sf::Texture I;
	sf::Texture J;
	sf::Texture K;
	sf::Texture L;
	sf::Texture M;
	sf::Texture N;
	sf::Texture O;
	sf::Texture P;
	sf::Texture Q;
	sf::Texture R;
	sf::Texture S;
	sf::Texture T;
	sf::Texture U;
	sf::Texture V;
	sf::Texture W;
	sf::Texture X;
	sf::Texture Y;
	sf::Texture Z;
	sf::Texture sp;

	std::vector<sf::Texture*> characterTextures
	{
		&A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z, &sp,
	};

	void createFontTextures() 
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
	
public:
	sf::RectangleShape textRect;
	uint8_t textRed{ 155 };
	uint8_t textGreen{ 0 };
	uint8_t textBlue{ 155 };
	sf::Vector2f startPos;
	Font()
	{
		startPos = sf::Vector2f(50, 50);
		createFontTextures();
	}

    bool attachCharTextureToRect(char input)
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
		default:
			return false;
			break;
		}
    }

	void setPos(sf::Vector2f newPos)
	{
		startPos = newPos;
	}

	sf::Vector2f getPos()
	{
		return startPos;
	}

	void setColor(uint8_t red, uint8_t green, uint8_t blue)
	{
		if (textRed == red && textGreen == green && textBlue == blue) { return; }
		textRed = red;
		textGreen = green;
		textBlue = blue;
		createFontTextures();
	}

};