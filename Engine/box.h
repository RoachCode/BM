#pragma once
#include <SFML/Graphics.hpp>

class Box
{
private:
	std::vector<bool> m_cornerArray
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
	void m_initCorner()
	{
		int size{ 14 };
		cornerTexture.create(size, size);
		cornerTextureBlack.create(size, size);
		sf::Uint8* pixels = new sf::Uint8[size * size * 4];
		sf::Uint8* pixelsBlack = new sf::Uint8[size * size * 4];

		for (int i = 0; i < m_cornerArray.size(); i++)
		{
			if (m_cornerArray[i] == 0)
			{
				pixels[(i * 4) + 0] = sf::Uint8(0);
				pixels[(i * 4) + 1] = sf::Uint8(0);
				pixels[(i * 4) + 2] = sf::Uint8(0);
				pixels[(i * 4) + 3] = sf::Uint8(0);

				pixelsBlack[(i * 4) + 0] = sf::Uint8(0);
				pixelsBlack[(i * 4) + 1] = sf::Uint8(0);
				pixelsBlack[(i * 4) + 2] = sf::Uint8(0);
				pixelsBlack[(i * 4) + 3] = sf::Uint8(0);
			}
			else
			{
				pixels[(i * 4) + 0] = borderColor.r;
				pixels[(i * 4) + 1] = borderColor.g;
				pixels[(i * 4) + 2] = borderColor.b;
				pixels[(i * 4) + 3] = sf::Uint8(255);

				pixelsBlack[(i * 4) + 0] = borderColorBlack.r;
				pixelsBlack[(i * 4) + 1] = borderColorBlack.g;
				pixelsBlack[(i * 4) + 2] = borderColorBlack.b;
				pixelsBlack[(i * 4) + 3] = sf::Uint8(255);
			}
		}

		cornerTexture.update(pixels);
		cornerTextureBlack.update(pixelsBlack);

		delete[] pixels;
		delete[] pixelsBlack;
	}

public:
	sf::Texture cornerTexture;
	sf::Texture cornerTextureBlack;
	int margin;
	int lineThickness;
	int borderOffset;
	int cornerSize;

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
		m_initCorner();
		background.setPrimitiveType(sf::Quads);
		border.setPrimitiveType(sf::Quads);
		borderBlack.setPrimitiveType(sf::Quads);
		topLeft = sf::Color(0, 0, 255, 55);
		topRight = sf::Color(0, 255, 0, 55);
		bottomRight = sf::Color(255, 0, 0, 55);
		bottomLeft = sf::Color(0, 0, 0, 55);

		borderOffset = 8;
		margin = 7;
		lineThickness = 6;
		cornerSize = 14;
	}

	void emptyContainers()
	{
		borderBlack.resize(0);
		border.resize(0);
		background.resize(0);
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
		#pragma region CORNERS
		sf::Vertex TLa;
		sf::Vertex TLb;
		sf::Vertex TLc;
		sf::Vertex TLd;
		TLa.position = pairF(startPosition.x - lineThickness, startPosition.y - lineThickness);
		TLb.position = pairF(startPosition.x - lineThickness + cornerSize, startPosition.y - lineThickness);
		TLc.position = pairF(startPosition.x - lineThickness + cornerSize, startPosition.y + cornerSize - lineThickness);
		TLd.position = pairF(startPosition.x - lineThickness, startPosition.y + cornerSize - lineThickness);
		TLd.texCoords = pairF(0.f, 0.f);
		TLa.texCoords = pairF(14.f, 0.f);
		TLb.texCoords = pairF(14.f, 14.f);
		TLc.texCoords = pairF(0.f, 14.f);
		border.append(TLa);
		border.append(TLb);
		border.append(TLc);
		border.append(TLd);

		sf::Vertex TRa;
		sf::Vertex TRb;
		sf::Vertex TRc;
		sf::Vertex TRd;
		TRa.position = pairF(startPosition.x - lineThickness + width - 2, startPosition.y - lineThickness);
		TRb.position = pairF(startPosition.x - lineThickness + width - 2 + cornerSize, startPosition.y - lineThickness);
		TRc.position = pairF(startPosition.x - lineThickness + width - 2 + cornerSize, startPosition.y + cornerSize - lineThickness);
		TRd.position = pairF(startPosition.x - lineThickness + width - 2, startPosition.y + cornerSize - lineThickness);
		TRa.texCoords = pairF(0.f, 0.f);
		TRb.texCoords = pairF(14.f, 0.f);
		TRc.texCoords = pairF(14.f, 14.f);
		TRd.texCoords = pairF(0.f, 14.f);
		border.append(TRa);
		border.append(TRb);
		border.append(TRc);
		border.append(TRd);

		sf::Vertex BRa;
		sf::Vertex BRb;
		sf::Vertex BRc;
		sf::Vertex BRd;
		BRa.position = pairF(startPosition.x - lineThickness + width - 2, startPosition.y - lineThickness + height - 2);
		BRb.position = pairF(startPosition.x - lineThickness + width - 2 + cornerSize, startPosition.y - lineThickness + height - 2);
		BRc.position = pairF(startPosition.x - lineThickness + width - 2 + cornerSize, startPosition.y + cornerSize - lineThickness + height - 2);
		BRd.position = pairF(startPosition.x - lineThickness + width - 2, startPosition.y + cornerSize - lineThickness + height - 2);
		BRb.texCoords = pairF(0.f, 0.f);
		BRc.texCoords = pairF(14.f, 0.f);
		BRd.texCoords = pairF(14.f, 14.f);
		BRa.texCoords = pairF(0.f, 14.f);
		border.append(BRa);
		border.append(BRb);
		border.append(BRc);
		border.append(BRd);

		sf::Vertex BLa;
		sf::Vertex BLb;
		sf::Vertex BLc;
		sf::Vertex BLd;
		BLa.position = pairF(startPosition.x - lineThickness, startPosition.y - lineThickness + height - 2);
		BLb.position = pairF(startPosition.x - lineThickness + cornerSize, startPosition.y - lineThickness + height - 2);
		BLc.position = pairF(startPosition.x - lineThickness + cornerSize, startPosition.y + cornerSize - lineThickness + height - 2);
		BLd.position = pairF(startPosition.x - lineThickness, startPosition.y + cornerSize - lineThickness + height - 2);
		BLc.texCoords = pairF(0.f, 0.f);
		BLd.texCoords = pairF(14.f, 0.f);
		BLa.texCoords = pairF(14.f, 14.f);
		BLb.texCoords = pairF(0.f, 14.f);
		border.append(BLa);
		border.append(BLb);
		border.append(BLc);
		border.append(BLd);
		
		size_t vertexCount{ border.getVertexCount() };
		for (int i = 0; i < vertexCount; i++)
		{
			sf::Vertex tempVertex;
			tempVertex = border[i];
			tempVertex.position = pairF(border[i].position.x + 1, border[i].position.y + 1);
			borderBlack.append(tempVertex);
		}
#pragma endregion

		#pragma region BORDERS
		sf::Vertex Ta;
		sf::Vertex Tb;
		sf::Vertex Tc;
		sf::Vertex Td;
		Ta.position = pairF(startPosition.x + borderOffset, startPosition.y - lineThickness);
		Tb.position = pairF(startPosition.x + width - borderOffset, startPosition.y - lineThickness);
		Tc.position = pairF(startPosition.x + width - borderOffset, startPosition.y);
		Td.position = pairF(startPosition.x + borderOffset, startPosition.y);
		Ta.color = borderColor;
		Tb.color = borderColor;
		Tc.color = borderColor;
		Td.color = borderColor;
		border.append(Ta);
		border.append(Tb);
		border.append(Tc);
		border.append(Td);

		sf::Vertex Ra;
		sf::Vertex Rb;
		sf::Vertex Rc;
		sf::Vertex Rd;
		Ra.position = pairF(startPosition.x + width, startPosition.y + borderOffset);
		Rb.position = pairF(startPosition.x + width + lineThickness, startPosition.y + borderOffset);
		Rc.position = pairF(startPosition.x + width + lineThickness, startPosition.y + height - borderOffset);
		Rd.position = pairF(startPosition.x + width, startPosition.y + height - borderOffset);
		Ra.color = borderColor;
		Rb.color = borderColor;
		Rc.color = borderColor;
		Rd.color = borderColor;
		border.append(Ra);
		border.append(Rb);
		border.append(Rc);
		border.append(Rd);

		sf::Vertex Ba;
		sf::Vertex Bb;
		sf::Vertex Bc;
		sf::Vertex Bd;
		Ba.position = pairF(startPosition.x + borderOffset, startPosition.y + height);
		Bb.position = pairF(startPosition.x + width - borderOffset, startPosition.y + height);
		Bc.position = pairF(startPosition.x + width - borderOffset, startPosition.y + height + lineThickness);
		Bd.position = pairF(startPosition.x + borderOffset, startPosition.y + height + lineThickness);
		Ba.color = borderColor;
		Bb.color = borderColor;
		Bc.color = borderColor;
		Bd.color = borderColor;
		border.append(Ba);
		border.append(Bb);
		border.append(Bc);
		border.append(Bd);

		sf::Vertex La;
		sf::Vertex Lb;
		sf::Vertex Lc;
		sf::Vertex Ld;
		La.position = pairF(startPosition.x - lineThickness, startPosition.y + borderOffset);
		Lb.position = pairF(startPosition.x, startPosition.y + borderOffset);
		Lc.position = pairF(startPosition.x, startPosition.y + height - borderOffset);
		Ld.position = pairF(startPosition.x - lineThickness, startPosition.y + height - borderOffset);
		La.color = borderColor;
		Lb.color = borderColor;
		Lc.color = borderColor;
		Ld.color = borderColor;
		border.append(La);
		border.append(Lb);
		border.append(Lc);
		border.append(Ld);

		// Black
		sf::Vertex TBa;
		sf::Vertex TBb;
		sf::Vertex TBc;
		sf::Vertex TBd;
		TBa.position = pairF(startPosition.x + borderOffset + 1, startPosition.y - lineThickness + 1);
		TBb.position = pairF(startPosition.x + width - borderOffset + 1, startPosition.y - lineThickness + 1);
		TBc.position = pairF(startPosition.x + width - borderOffset + 1, startPosition.y + 1);
		TBd.position = pairF(startPosition.x + borderOffset + 1, startPosition.y + 1);
		TBa.color = borderColorBlack;
		TBb.color = borderColorBlack;
		TBc.color = borderColorBlack;
		TBd.color = borderColorBlack;
		borderBlack.append(TBa);
		borderBlack.append(TBb);
		borderBlack.append(TBc);
		borderBlack.append(TBd);

		sf::Vertex RBa;
		sf::Vertex RBb;
		sf::Vertex RBc;
		sf::Vertex RBd;
		RBa.position = pairF(startPosition.x + width + 1, startPosition.y + borderOffset + 1);
		RBb.position = pairF(startPosition.x + width + lineThickness + 1, startPosition.y + borderOffset + 1);
		RBc.position = pairF(startPosition.x + width + lineThickness + 1, startPosition.y + height - borderOffset + 1);
		RBd.position = pairF(startPosition.x + width + 1, startPosition.y + height - borderOffset + 1);
		RBa.color = borderColorBlack;
		RBb.color = borderColorBlack;
		RBc.color = borderColorBlack;
		RBd.color = borderColorBlack;
		borderBlack.append(RBa);
		borderBlack.append(RBb);
		borderBlack.append(RBc);
		borderBlack.append(RBd);

		sf::Vertex BBa;
		sf::Vertex BBb;
		sf::Vertex BBc;
		sf::Vertex BBd;
		BBa.position = pairF(startPosition.x + borderOffset + 1, startPosition.y + height + 1);
		BBb.position = pairF(startPosition.x + width - borderOffset + 1, startPosition.y + height + 1);
		BBc.position = pairF(startPosition.x + width - borderOffset + 1, startPosition.y + height + lineThickness + 1);
		BBd.position = pairF(startPosition.x + borderOffset + 1, startPosition.y + height + lineThickness + 1);
		BBa.color = borderColorBlack;
		BBb.color = borderColorBlack;
		BBc.color = borderColorBlack;
		BBd.color = borderColorBlack;
		borderBlack.append(BBa);
		borderBlack.append(BBb);
		borderBlack.append(BBc);
		borderBlack.append(BBd);

		sf::Vertex LBa;
		sf::Vertex LBb;
		sf::Vertex LBc;
		sf::Vertex LBd;
		LBa.position = pairF(startPosition.x - lineThickness + 1, startPosition.y + borderOffset + 1);
		LBb.position = pairF(startPosition.x + 1, startPosition.y + borderOffset + 1);
		LBc.position = pairF(startPosition.x + 1, startPosition.y + height - borderOffset + 1);
		LBd.position = pairF(startPosition.x - lineThickness + 1, startPosition.y + height - borderOffset + 1);
		LBa.color = borderColorBlack;
		LBb.color = borderColorBlack;
		LBc.color = borderColorBlack;
		LBd.color = borderColorBlack;
		borderBlack.append(LBa);
		borderBlack.append(LBb);
		borderBlack.append(LBc);
		borderBlack.append(LBd);

#pragma endregion

	}

	void setBackgroundAlpha(sf::Uint8 alpha)
	{
		topLeft.a = alpha;
		topRight.a = alpha;
		bottomRight.a = alpha;
		bottomLeft.a = alpha;
	}
	void setBackgroundColor(sf::Color colorIn)
	{
		topLeft = colorIn;
		topRight = colorIn;
		bottomRight = colorIn;
		bottomLeft = colorIn;
	}
	void setBackgroundColor(sf::Color colorInTL, sf::Color colorInTR, sf::Color colorInBL, sf::Color colorInBR)
	{
		topLeft = colorInTL;
		topRight = colorInTR;
		bottomRight = colorInBR;
		bottomLeft = colorInBL;
	}
};