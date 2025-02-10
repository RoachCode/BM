#pragma once
#include <SFML/Graphics.hpp>
#include "view.h"

class Box : protected View
{
private:
	std::vector<bool> cornerArray
	{
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	};
	void initCorner()
	{
		// get values from View class
		int pixelSize{ getPixelSize() };

		int size{ 14 };
		cornerTexture.create(size, size);
		sf::Uint8* pixels = new sf::Uint8[size * size * 4];

		for (int i = 0; i < cornerArray.size(); i++)
		{
			if (cornerArray[i] == 0)
			{
				pixels[(i * 4) + 0] = borderColor.r;
				pixels[(i * 4) + 1] = borderColor.g;
				pixels[(i * 4) + 2] = borderColor.b;
				pixels[(i * 4) + 3] = sf::Uint8(0);
			}
			else
			{
				pixels[(i * 4) + 0] = borderColor.r;
				pixels[(i * 4) + 1] = borderColor.g;
				pixels[(i * 4) + 2] = borderColor.b;
				pixels[(i * 4) + 3] = sf::Uint8(255);
			}
		}


		cornerTexture.update(pixels);
		corner.setTexture(cornerTexture);
		delete[] pixels;

		corner.setScale(pixelSize, pixelSize);
		//corner.setPosition(pairF(800, 600));
	}
	sf::Sprite corner;
	sf::Texture cornerTexture;

public:

	int margin;
	int lineThickness;
	int borderOffset;
	int cornerSize;

	std::vector<sf::Sprite> spriteContainer;
	std::vector<sf::Sprite> spriteContainerBlack;

	sf::VertexArray border;
	sf::VertexArray borderBlack;
	sf::VertexArray background;

	sf::Color topLeft;
	sf::Color topRight;
	sf::Color bottomRight;
	sf::Color bottomLeft;
	sf::Color borderColor;
	sf::Color borderColorBlack;

	Box()
	{
		borderColor = sf::Color::White;
		borderColorBlack = sf::Color::Black;
		initCorner();
		background.setPrimitiveType(sf::Quads);
		border.setPrimitiveType(sf::Quads);
		borderBlack.setPrimitiveType(sf::Quads);
		topLeft = sf::Color(0, 0, 255, 55);
		topRight = sf::Color(0, 255, 0, 55);
		bottomRight = sf::Color(255, 0, 0, 55);
		bottomLeft = sf::Color(0, 0, 0, 55);

		int pixelSize{ getPixelSize() };
		borderOffset = 8 * pixelSize;
		margin = 7 * pixelSize;
		lineThickness = 6 * pixelSize;
		cornerSize = 14 * pixelSize;
		corner.setScale(pairF(pixelSize, pixelSize));
	}

	void emptyContainers()
	{
		borderBlack.resize(0);
		border.resize(0);
		background.resize(0);
		spriteContainer.clear();
		spriteContainerBlack.clear();
	}
	void createBackground(sf::Vector2f startPosition, int width, int height)
	{
		sf::Vertex a;
		sf::Vertex b;
		sf::Vertex c;
		sf::Vertex d;

		a.position = startPosition;
		b.position = pairF(startPosition.x + width, startPosition.y);
		c.position = pairF(startPosition.x + width, startPosition.y + height);
		d.position = pairF(startPosition.x, startPosition.y + height);

		a.color = topLeft;
		b.color = topRight;
		c.color = bottomRight;
		d.color = bottomLeft;

		background.append(a);
		background.append(b);
		background.append(c);
		background.append(d);
	}
	void createBorders(sf::Vector2f startPosition, int width, int height)
	{
		// get values from View class
		int pixelSize{ getPixelSize() };

#pragma region CORNERS
		// Background
		corner.setColor(borderColorBlack);
		corner.setRotation(270.f);
		corner.setPosition(pairF(startPosition.x - cornerSize / 2 + pixelSize + pixelSize, startPosition.y + cornerSize / 2 + pixelSize + pixelSize));
		spriteContainerBlack.push_back(corner);

		corner.setRotation(0.f);
		corner.setPosition(pairF(startPosition.x + width - cornerSize / 2 - pixelSize + pixelSize, startPosition.y - cornerSize / 2 + pixelSize + pixelSize));
		spriteContainerBlack.push_back(corner);

		corner.setRotation(90.f);
		corner.setPosition(pairF(startPosition.x + width + cornerSize / 2 - pixelSize + pixelSize, startPosition.y + height - cornerSize / 2 - pixelSize + pixelSize));
		spriteContainerBlack.push_back(corner);

		corner.setRotation(180.f);
		corner.setPosition(pairF(startPosition.x + cornerSize / 2 + pixelSize + pixelSize, startPosition.y + height + cornerSize / 2 - pixelSize + pixelSize));
		spriteContainerBlack.push_back(corner);

		// Foreground
		corner.setColor(borderColor);
		corner.setRotation(270.f);
		corner.setPosition(pairF(startPosition.x - cornerSize / 2 + pixelSize, startPosition.y + cornerSize / 2 + pixelSize));
		spriteContainer.push_back(corner);

		corner.setRotation(0.f);
		corner.setPosition(pairF(startPosition.x + width - cornerSize / 2 - pixelSize, startPosition.y - cornerSize / 2 + pixelSize));
		spriteContainer.push_back(corner);

		corner.setRotation(90.f);
		corner.setPosition(pairF(startPosition.x + width + cornerSize / 2 - pixelSize, startPosition.y + height - cornerSize / 2 - pixelSize));
		spriteContainer.push_back(corner);

		corner.setRotation(180.f);
		corner.setPosition(pairF(startPosition.x + cornerSize / 2 + pixelSize, startPosition.y + height + cornerSize / 2 - pixelSize));
		spriteContainer.push_back(corner);
#pragma endregion

#pragma region BORDERS
		sf::Vertex Ta;
		sf::Vertex Tb;
		sf::Vertex Tc;
		sf::Vertex Td;
		Ta.position = pairF(startPosition.x + borderOffset + pixelSize, startPosition.y - lineThickness + pixelSize);
		Tb.position = pairF(startPosition.x + width - borderOffset + pixelSize, startPosition.y - lineThickness + pixelSize);
		Tc.position = pairF(startPosition.x + width - borderOffset + pixelSize, startPosition.y + pixelSize);
		Td.position = pairF(startPosition.x + borderOffset + pixelSize, startPosition.y + pixelSize);
		Ta.color = borderColorBlack;
		Tb.color = borderColorBlack;
		Tc.color = borderColorBlack;
		Td.color = borderColorBlack;
		borderBlack.append(Ta);
		borderBlack.append(Tb);
		borderBlack.append(Tc);
		borderBlack.append(Td);

		sf::Vertex Ra;
		sf::Vertex Rb;
		sf::Vertex Rc;
		sf::Vertex Rd;
		Ra.position = pairF(startPosition.x + width + pixelSize, startPosition.y + borderOffset + pixelSize);
		Rb.position = pairF(startPosition.x + width + lineThickness + pixelSize, startPosition.y + borderOffset + pixelSize);
		Rc.position = pairF(startPosition.x + width + lineThickness + pixelSize, startPosition.y + height - borderOffset + pixelSize);
		Rd.position = pairF(startPosition.x + width + pixelSize, startPosition.y + height - borderOffset + pixelSize);
		Ra.color = borderColorBlack;
		Rb.color = borderColorBlack;
		Rc.color = borderColorBlack;
		Rd.color = borderColorBlack;
		borderBlack.append(Ra);
		borderBlack.append(Rb);
		borderBlack.append(Rc);
		borderBlack.append(Rd);

		sf::Vertex Ba;
		sf::Vertex Bb;
		sf::Vertex Bc;
		sf::Vertex Bd;
		Ba.position = pairF(startPosition.x + borderOffset + pixelSize, startPosition.y + height + pixelSize);
		Bb.position = pairF(startPosition.x + width - borderOffset + pixelSize, startPosition.y + height + pixelSize);
		Bc.position = pairF(startPosition.x + width - borderOffset + pixelSize, startPosition.y + height + lineThickness + pixelSize);
		Bd.position = pairF(startPosition.x + borderOffset + pixelSize, startPosition.y + height + lineThickness + pixelSize);
		Ba.color = borderColorBlack;
		Bb.color = borderColorBlack;
		Bc.color = borderColorBlack;
		Bd.color = borderColorBlack;
		borderBlack.append(Ba);
		borderBlack.append(Bb);
		borderBlack.append(Bc);
		borderBlack.append(Bd);

		sf::Vertex La;
		sf::Vertex Lb;
		sf::Vertex Lc;
		sf::Vertex Ld;
		La.position = pairF(startPosition.x - lineThickness + pixelSize, startPosition.y + borderOffset + pixelSize);
		Lb.position = pairF(startPosition.x + pixelSize, startPosition.y + borderOffset + pixelSize);
		Lc.position = pairF(startPosition.x + pixelSize, startPosition.y + height - borderOffset + pixelSize);
		Ld.position = pairF(startPosition.x - lineThickness + pixelSize, startPosition.y + height - borderOffset + pixelSize);
		La.color = borderColorBlack;
		Lb.color = borderColorBlack;
		Lc.color = borderColorBlack;
		Ld.color = borderColorBlack;
		borderBlack.append(La);
		borderBlack.append(Lb);
		borderBlack.append(Lc);
		borderBlack.append(Ld);

		size_t vertexCount{ borderBlack.getVertexCount() };
		for (int i = 0; i < vertexCount; i++)
		{
			sf::Vertex tempVertex;
			tempVertex.position = pairF(borderBlack[i].position.x - pixelSize, borderBlack[i].position.y - pixelSize);
			tempVertex.color = borderColor;
			border.append(tempVertex);
		}
#pragma endregion

	}

	void setAlpha(sf::Uint8 alpha)
	{
		topLeft.a = alpha;
		topRight.a = alpha;
		bottomRight.a = alpha;
		bottomLeft.a = alpha;
	}
	void setColor(sf::Color colorIn)
	{
		topLeft = colorIn;
		topRight = colorIn;
		bottomRight = colorIn;
		bottomLeft = colorIn;
	}
	void setColor(sf::Color colorInTL, sf::Color colorInTR, sf::Color colorInBL, sf::Color colorInBR)
	{
		topLeft = colorInTL;
		topRight = colorInTR;
		bottomRight = colorInBR;
		bottomLeft = colorInBL;
	}
};