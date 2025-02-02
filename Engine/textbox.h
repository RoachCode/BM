#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "view.h"
#include "font.h"

class TextBox : public View, public Font
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

public:
    sf::Sprite corner;
    sf::Texture cornerTexture;
	std::vector<sf::Sprite> spriteContainer;
	std::vector<sf::Sprite> spriteContainerBlack;

	std::vector<FontMap> fontContainer;

    sf::VertexArray border;
    sf::VertexArray borderBlack;
    sf::VertexArray background;

    sf::Color topLeft;
    sf::Color topRight;
    sf::Color bottomRight;
    sf::Color bottomLeft;
    sf::Color borderColor;
    sf::Color borderColorBlack;

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
        corner.setPosition(pairF(800, 600));
    }

    TextBox()
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
    }

	void createText(std::string string, int maxTilesPerRow)
	{
		Font::currentString.clear();
		for (size_t j = 0; j < string.length(); j++)
		{
			const char letter = string[j];
			const int letterNumber{ Font::getRectOffset(letter) };
			if (Font::getRectOffset(letter) < 207)
			{
				Font::currentString.push_back(letterNumber + 0);
				Font::currentString.push_back(letterNumber + 1);
				Font::currentString.push_back(letterNumber + 2);
			}
			else if (Font::getRectOffset(letter) < 231)
			{
				Font::currentString.push_back(letterNumber + 0);
				Font::currentString.push_back(letterNumber + 1);
				Font::currentString.push_back(letterNumber + 2);
				Font::currentString.push_back(letterNumber + 3);
			}
			else
			{
				Font::currentString.push_back(letterNumber + 0);
			}
			// kerning space (2 pixels)
			if (j < string.length() - 1 && letter != ' ') { Font::currentString.push_back(78); }

			// check to see if the word will fit on this row (including following punctuation)
			if (string[j] == ' ' && maxTilesPerRow != 0)
			{
				int tilesInWord{ 4 }; //starts with a space. supposed to be 3 but this works for some reason.
				int iterator{ 1 };
				while (string[j + iterator] != ' ' && j + iterator < string.length())
				{
					if (Font::getRectOffset(letter) < 207)
					{
						tilesInWord += 3;
					}
					else if (Font::getRectOffset(letter) < 231)
					{
						tilesInWord += 4;
					}
					else
					{
						tilesInWord += 1;
					}
					//kerning if the word isn't finished
					if (string[j + iterator + 1] != ' ')
					{
						tilesInWord += 1;
					}
					iterator += 1;
				}

				// get current position in the line
				int tilePosition{ intify(Font::currentString.size()) };
				while (tilePosition > maxTilesPerRow) { tilePosition -= maxTilesPerRow; }

				// if the word won't fit, use kerning spaces to finish the line
				if (tilePosition + tilesInWord > maxTilesPerRow)
				{
					int remainingTiles{ maxTilesPerRow - tilePosition };
					for (int i = 0; i < remainingTiles; i++) { Font::currentString.push_back(78); }
				}
			}
		}
	}

	void createTextBox(int boundingWidth, int messageRows, int fontScale, sf::Vector2f startPosition)
	{
		const int pixelSize{ getPixelSize() };
		const int margin{ 6 * pixelSize };
		const int width{ boundingWidth + margin * 2 };
		const int height{ messageRows * 10 * fontScale + fontScale + margin * 2 };
		const sf::Vector2f pos(pairF(startPosition.x - margin - pixelSize, startPosition.y - margin - pixelSize));

		createBackground(pos, width, height);
		createBorders(pos, width, height);
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
		const int cornerSize{ 14 * pixelSize };
		const int lineThickness{ 6 * pixelSize };
		const int borderOffset{ 8 * pixelSize };

		#pragma region CORNERS
		// Background
		corner.setColor(borderColorBlack);
		corner.setRotation(270.f);
		corner.setPosition(pairF(startPosition.x - cornerSize / 2 + pixelSize + pixelSize, startPosition.x + cornerSize / 2 + pixelSize + pixelSize));
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
		corner.setPosition(pairF(startPosition.x - cornerSize / 2 + pixelSize, startPosition.x + cornerSize / 2 + pixelSize));
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

	void emptyContainers()
	{
		borderBlack.resize(0);
		border.resize(0);
		background.resize(0);
		spriteContainer.clear();
		spriteContainerBlack.clear();
		fontContainer.clear();
	}
	void addText(std::string string, sf::Vector2f startPosition, int scale, int boundingWidth)
	{
		// get values from View class
		int pixelSize{ getPixelSize() };
		const int fontScale{ scale * pixelSize };

		// tiles are two pixels wide
		int maxTilesPerRow{ (boundingWidth == 0) ? 0 : boundingWidth / (2 * fontScale) };

		createText(string, maxTilesPerRow);
		
		// add blank characters to the end to complete the tilemap or shrink to fit
		int messageTileCount{ intify(Font::currentString.size()) };
		int messageWidthInTiles{ messageTileCount > maxTilesPerRow && maxTilesPerRow != 0 ? maxTilesPerRow : messageTileCount };
		int messageWidthInPixels{ messageWidthInTiles * 2 * fontScale + fontScale };
		if (messageWidthInPixels < boundingWidth) { boundingWidth = messageWidthInPixels; }

		// If no bounding box was specified, stay in the view.
		if (maxTilesPerRow == 0)
		{
			maxTilesPerRow = messageTileCount;
			boundingWidth = messageWidthInPixels;
			// Bounds Right
			if ((intify(startPosition.x) + messageWidthInPixels) > intify(getViewCoordinates(UR).x))
			{
				startPosition.x = floatify(getViewCoordinates(UR).x - messageWidthInPixels);
			}
			// Bounds Left
			if (intify(startPosition.x) < getViewCoordinates(UL).x)
			{
				startPosition.x = getViewCoordinates(UL).x;
			}
			// Bounds Bottom
			if (intify(startPosition.y) + 10 > intify(getViewCoordinates(DR).y))
			{
				startPosition.y = floatify(getViewCoordinates(DR).y - (10 * fontScale) - fontScale);
			}
			// Bounds Top
			if (intify(startPosition.y) < getViewCoordinates(UL).y)
			{
				startPosition.y = getViewCoordinates(UL).y;
			}
		}
		while (messageTileCount % maxTilesPerRow != 0)
		{
			Font::currentString.push_back(78);
			messageTileCount += 1;
		}

		int messageRows{ messageTileCount / maxTilesPerRow };

		createTextBox(boundingWidth, messageRows, fontScale, startPosition);

		// create font map
		Font::fontMap.setScale(pairF(fontScale, fontScale));

		Font::fontMap.setPosition(pairF(startPosition.x + fontScale, startPosition.y + fontScale));
		Font::setColor(sf::Color(44, 44, 44), true);
		Font::fontMap.load(Font::fontImage, sf::Vector2u(2, 10), Font::currentString, messageWidthInTiles, messageRows);
		fontContainer.push_back(Font::fontMap);

		Font::fontMap.setPosition(startPosition);
		Font::setColor(sf::Color(Font::textRed, Font::textGreen, Font::textBlue));
		Font::fontMap.load(Font::fontImage, sf::Vector2u(2, 10), Font::currentString, messageWidthInTiles, messageRows);
		fontContainer.push_back(Font::fontMap);

	}

};