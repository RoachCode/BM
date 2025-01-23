#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "tilemap.h"

/*
class Font2
{
private:

public:
	sf::Uint8 textRed{ 255 };
	sf::Uint8 textGreen{ 255 };
	sf::Uint8 textBlue{ 255 };
	sf::Vector2f startPos{ sf::Vector2f(50.f, 50.f) };

	// AthroughTildeData
#pragma region
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

		// a
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 0, 1,

		// b
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,

		// c
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,

		// d
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,

		// e
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,

		// f
		0, 0, 1, 1, 1, 1,
		0, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 0, 0,

		// g
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// h
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// i
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 0,

		// j
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// k
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,

		// l
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,

		// m
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,

		// n
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,

		// o
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// p
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,

		// q
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,

		// r
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,

		// s
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// t
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 0,

		// u
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// v
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,

		// w
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 0,

		// x
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,

		// y
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// z
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1,

		// ?
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,

		// !
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,

		// @
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1,
		1, 0, 1, 0, 1, 1,
		1, 0, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,

		// #
		0, 0, 0, 1, 0, 1,
		0, 0, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 1, 0,
		0, 0, 1, 0, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 1, 0, 1, 0, 0,
		0, 1, 0, 1, 0, 0,

		// $
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 1, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 1, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// ~
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 1,
		0, 1, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0


	};
	#pragma endregion
	std::vector<bool> specialChars
	{
		// ^ SWORD
		1, 0, 1, 1, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 0, 0, 0, 0,
		1, 0, 1, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 1, 1,

		// | STAFF
		0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 1,

		// _ POTION
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 0, 0,

		// < AXE
		1, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 1,

		// = KEY
		1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 1,

		// { BOW
		1, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 1, 0, 0,
		0, 0, 1, 1, 0, 0, 1, 0,
		0, 0, 0, 1, 1, 0, 0, 1,
		0, 0, 0, 0, 1, 1, 1, 1

	};
	std::vector<bool> punctuationChars
	{
		// :
		0, 0,
		0, 0,
		1, 1,
		1, 1,
		0, 0,
		1, 1,
		1, 1,
		0, 0,

		// .
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		1, 1,
		1, 1,

		// ,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		1, 1,
		1, 1,
		0, 1,
		1, 0
	};
	sf::Image fontImage;
	sf::Image fontSpecialImage;
	sf::Image fontPunctuationImage;
	sf::Texture fontTexture;
	sf::Texture fontSpecialTexture;
	sf::Texture fontPunctuationTexture;

	sf::Sprite charSprite;
	// Sets character kerning
	sf::Vector2f moveR{ sf::Vector2f(7.f, 0.f) };
	sf::Vector2i addon{ sf::Vector2i(0, 0) };
	Font2();
	void createFontImageAndTexture(sf::Color color = sf::Color(sf::Color(255, 120, 10)));
	void setColor(sf::Color colorIn, bool ignoreReassign = false);
	bool attachCharImageSubRectToSprite(char input);
	sf::Vector2f getPos();
	void setPos(sf::Vector2f newPos);
	sf::Vector2f getStartPos();
	void setStartPos(sf::Vector2f newPos = sf::Vector2f(50.f, 50.f));
	void move(sf::Vector2f offset);
	int getRectOffset(char input);
	const sf::Color alphaKey{ sf::Color(69,69,69) };
	void setCharTextureToSprite(int pixPerChar, int charCount, int width, sf::Image& image, sf::Texture& texture);
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;)

	// Moving text to vertexArray
	//sf::Vertex
};
*/

class Font
{
private:

public:
	std::vector<bool> textCharacters
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
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// B
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// C
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// D
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// E
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// F
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// G
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// H
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// I
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// J
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// K
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// L
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// M
		1, 0, 0, 0, 0, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// N
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// O
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// P
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// Q
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// R
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// S
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// T
		1, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// U
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// V
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// W
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// X
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// Y
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// Z
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// sp
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
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
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 1
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 2
		1, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 1,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 3
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 4
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 5
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 6
		0, 1, 1, 1, 1, 0,
		1, 1, 1, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 7
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 8
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// 9
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 1, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// a
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 0, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// b
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// c
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// d
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// e
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// f
		0, 0, 1, 1, 1, 1,
		0, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// g
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// h
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// i
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// j
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// k
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// l
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// m
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// n
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// o
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// p
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,

		// q
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 1,

		// r
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// s
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// t
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// u
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// v
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 0, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// w
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// x
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// y
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 1, 1, 1, 1, 0,

		// z
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 1,
		0, 0, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0,
		1, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// ?
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// !
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// @
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1,
		1, 0, 1, 0, 1, 1,
		1, 0, 1, 1, 1, 0,
		1, 1, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// #
		0, 0, 0, 1, 0, 1,
		0, 0, 0, 1, 0, 1,
		0, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 1, 0,
		0, 0, 1, 0, 1, 0,
		1, 1, 1, 1, 1, 1,
		0, 1, 0, 1, 0, 0,
		0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// $
		0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 1,
		1, 1, 0, 1, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 1, 0, 1, 1,
		1, 1, 1, 0, 1, 1,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,

		// ~
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 1,
		0, 1, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
	};
	std::vector<bool> specialCharacters
	{

		// ^ SWORD
		1, 0, 1, 1, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 0, 0, 0, 0,
		1, 0, 1, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,

		// | STAFF
		0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,

		// _ POTION
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,

		// < AXE
		1, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,

		// = KEY
		1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,

		// { BOW
		1, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 0, 0, 0, 0,
		1, 1, 0, 0, 1, 0, 0, 0,
		0, 1, 1, 0, 0, 1, 0, 0,
		0, 0, 1, 1, 0, 0, 1, 0,
		0, 0, 0, 1, 1, 0, 0, 1,
		0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
	std::vector<bool> punctuationCharacters
	{
		// :
		0, 0,
		0, 0,
		1, 1,
		1, 1,
		0, 0,
		1, 1,
		1, 1,
		0, 0,
		0, 0,
		0, 0,

		// .
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		1, 1,
		1, 1,
		0, 0,
		0, 0,

		// ,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		1, 1,
		1, 1,
		0, 1,
		1, 0,
	};

	const int tileWidthUnit{ 16 };
	sf::Image fontImage;
	sf::Texture fontTexture;
	sf::Uint8 textRed{ 255 };
	sf::Uint8 textGreen{ 255 };
	sf::Uint8 textBlue{ 255 };
	sf::Vector2f startPos{ sf::Vector2f(50.f, 50.f) };
	const sf::Color alphaKey{ sf::Color(69,69,69) };

	Font()
	{
		createFontImageAndTexture();
		loadTileMap();
	}

	void setColor(sf::Color colorIn, bool ignoreReassign = false)
	{
		if (!ignoreReassign)
		{
			textRed = sf::Uint8(colorIn.r);
			textGreen = sf::Uint8(colorIn.g);
			textBlue = sf::Uint8(colorIn.b);
		}

		for (int i = 0; i < fontImage.getSize().x; i++)
		{
			for (int j = 0; j < fontImage.getSize().y; j++)
			{
				sf::Color color = fontImage.getPixel(i, j);
				if (color.r != alphaKey.r && color.g != alphaKey.g && color.b != alphaKey.b)
				{
					fontImage.setPixel(i, j, colorIn);
				}
			}
		}
		fontTexture.loadFromImage(fontImage);
	}

	void createFontImageAndTexture(sf::Color color = sf::Color(sf::Color(255, 120, 10)))
	{
		const int height{ 10 };
		const int fullWidth{ intify(textCharacters.size() + specialCharacters.size() + punctuationCharacters.size()) / height };
		fontImage.create(fullWidth, height);

		const int pixPerText{ 60 };
		const int pixPerSpec{ 80 };
		const int pixPerPunc{ 20 };

		const int charCountText{ 69 };
		const int charCountSpec{ 6 };
		const int charCountPunc{ 3 };

		const int charWidthText{ 6 };
		const int charWidthSpec{ 8 };
		const int charWidthPunc{ 2 };

		int pixelCount{ charCountText * pixPerText };
		int width{ pixelCount / height };
		for (int i = 0; i < charCountText; i++)
		{
			sf::Uint8* pixels = new sf::Uint8[pixelCount * 4];
			for (int j = 0; j < pixPerText; j++)
			{
				if (textCharacters[j + i * pixPerText] == true)
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
			sf::Image textImage;
			textImage.create(charWidthText, height, pixels);

			delete[] pixels;
			fontImage.copy(textImage, i * charWidthText, 0);

		}

		pixelCount = charCountSpec * pixPerSpec;
		width = pixelCount / height;
		for (int i = 0; i < charCountSpec; i++)
		{
			sf::Uint8* pixels = new sf::Uint8[pixelCount * 4];
			for (int j = 0; j < pixPerSpec; j++)
			{
				if (specialCharacters[j + i * pixPerSpec] == true)
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
			sf::Image specImage;
			specImage.create(charWidthSpec, height, pixels);

			delete[] pixels;
			fontImage.copy(specImage, (charWidthText * charCountText) + (i * charWidthSpec), 0);

		}

		pixelCount = charCountPunc * pixPerPunc;
		width = pixelCount / height;
		for (int i = 0; i < charCountPunc; i++)
		{
			sf::Uint8* pixels = new sf::Uint8[pixelCount * 4];
			for (int j = 0; j < pixPerPunc; j++)
			{
				if (punctuationCharacters[j + i * pixPerPunc] == true)
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
			sf::Image puncImage;
			puncImage.create(charWidthPunc, height, pixels);

			delete[] pixels;
			fontImage.copy(puncImage, (charWidthText * charCountText) + (charWidthSpec * charCountSpec) + i * charWidthPunc, 0);

		}

		fontTexture.create(fullWidth, height);
		fontTexture.loadFromImage(fontImage);
		setColor(color);
	}

	std::vector<int> currentString = { 0, 1, 2, 3, 4, 5 };
	int getRectOffset(char input)
	{
		switch (input)
		{
		case 'A': return 0;
		case 'B': return 3;
		case 'C': return 6;
		case 'D': return 9;
		case 'E': return 12;
		case 'F': return 15;
		case 'G': return 18;
		case 'H': return 21;
		case 'I': return 24;
		case 'J': return 27;
		case 'K': return 30;
		case 'L': return 33;
		case 'M': return 36;
		case 'N': return 39;
		case 'O': return 42;
		case 'P': return 45;
		case 'Q': return 48;
		case 'R': return 51;
		case 'S': return 54;
		case 'T': return 57;
		case 'U': return 60;
		case 'V': return 63;
		case 'W': return 66;
		case 'X': return 69;
		case 'Y': return 72;
		case 'Z': return 75;
		case ' ': return 78;
		case '0': return 81;
		case '1': return 84;
		case '2': return 87;
		case '3': return 90;
		case '4': return 93;
		case '5': return 96;
		case '6': return 99;
		case '7': return 102;
		case '8': return 105;
		case '9': return 108;
		case 'a': return 111;
		case 'b': return 114;
		case 'c': return 117;
		case 'd': return 120;
		case 'e': return 123;
		case 'f': return 126;
		case 'g': return 129;
		case 'h': return 132;
		case 'i': return 135;
		case 'j': return 138;
		case 'k': return 141;
		case 'l': return 144;
		case 'm': return 147;
		case 'n': return 150;
		case 'o': return 153;
		case 'p': return 156;
		case 'q': return 159;
		case 'r': return 162;
		case 's': return 165;
		case 't': return 168;
		case 'u': return 171;
		case 'v': return 174;
		case 'w': return 177;
		case 'x': return 180;
		case 'y': return 183;
		case 'z': return 186;
		case '?': return 189;
		case '!': return 192;
		case '@': return 195;
		case '#': return 198;
		case '$': return 201;
		case '~': return 204;
		case '^': return 207;//
		case '|': return 211;
		case '_': return 215;
		case '<': return 219;
		case '=': return 223;
		case '{': return 227;
		case ':': return 231;//
		case '.': return 232;
		case ',': return 233;
		default:
			std::cout << "character missing: " << input << '\n';
			return -1;
		}
	};

	FontMap fontMap;

	//possibly unnecessary function?
	void loadTileMap()
	{
		//fontMap.load(fontImage, sf::Vector2u(2, 8), placeholderArray, 6, 8);
		fontMap.setScale(pairF(2.999, 2.999));
		// how many tiles in width, how many tiles in height - are the last two parameters

		fontMap.load(fontImage, sf::Vector2u(2, 10), currentString, currentString.size(), 1);
	}
};