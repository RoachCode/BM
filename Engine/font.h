#pragma once
#include <SFML/Graphics.hpp>
/*
extern class Font
{
private:

	// the first 69 cgaracters can fit in this format
	std::vector<bool> AthroughTildeData
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

		// 0
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 1
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,

		// 2
		1, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 1,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1,

		// 3
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 4
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 0,

		// 5
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 6
		0, 1, 1, 1, 1, 0,
		1, 1, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 7
		1, 1, 1, 1, 1, 0,
		1, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,

		// 8
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 9
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,



	};
	std::vector<sf::Texture*> characterTextures
	{
		&A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K, &L, &M, &N, &O, &P, &Q, &R, &S, &T, &U, &V, &W, &X, &Y, &Z, &sp, 
		//&a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z, 
		&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine,
	};

	//Textures region (tidying)
#pragma region
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
	sf::Texture zero;
	sf::Texture one;
	sf::Texture two;
	sf::Texture three;
	sf::Texture four;
	sf::Texture five;
	sf::Texture six;
	sf::Texture seven;
	sf::Texture eight;
	sf::Texture nine;
#pragma endregion

	void createFontTextures();
	

	uint8_t textRed{ 255 };
	uint8_t textGreen{ 255 };
	uint8_t textBlue{ 255 };
	sf::RectangleShape textRect;
	sf::Vector2f startPos;


public:


	sf::RectangleShape getRect();


	Font();
	bool attachCharTextureToRect(char input);
	void setPos(sf::Vector2f newPos);
	sf::Vector2f getPos();
	void setColor(uint8_t red, uint8_t green, uint8_t blue);
	void move(sf::Vector2f offset);
	void setStartPos(sf::Vector2f startPosition);
	sf::Vector2f getStartPos();
};
*/
extern class Font2
{
private:

public:
	sf::Uint8 textRed{ 255 };
	sf::Uint8 textGreen{ 255 };
	sf::Uint8 textBlue{ 255 };
	sf::Vector2f startPos{ sf::Vector2f(50.f, 50.f) };
	std::vector<bool> AthroughTildeData
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

		// 0
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 1
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,

		// 2
		1, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 1,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1,

		// 3
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 4
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 0,

		// 5
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 6
		0, 1, 1, 1, 1, 0,
		1, 1, 1, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 7
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,

		// 8
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// 9
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,



	};
	sf::Image fontImage;
	sf::Texture fontTexture;
	sf::Sprite charSprite;
	// Sets character kerning
	sf::Vector2f moveR{ sf::Vector2f(7.f, 0.f) };
	Font2();
	void createFontImageAndTexture();
	void setColor(sf::Color colorIn, bool ignoreReassignment = false);
	bool attachCharImageSubRectToSprite(char input);
	sf::Vector2f getPos();
	void setPos(sf::Vector2f newPos);
	sf::Vector2f getStartPos();
	void setStartPos(sf::Vector2f newPos = sf::Vector2f(50.f, 50.f));
	void move(sf::Vector2f offset);
	int getRectOffset(char input);
	const sf::Color alphaKey{ sf::Color(69,69,69) };
	void resetImage(sf::Color colorIn2);

	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;)
};