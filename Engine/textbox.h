#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "view.h"
#include "font.h"
#include "box.h"
#include "tilemap.h"

class TextBox : protected View, protected Font
{
private:
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

public:
	Box box;
	std::vector<FontMap> fontContainer;

	void emptyContainers()
	{
		box.emptyContainers();
		fontContainer.clear();
	}
	void addText(std::string string, sf::Vector2f startPosition, int scale, int boundingWidth, bool background, bool borders)
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
		int messageWidthInPixels{ messageWidthInTiles * 2 * fontScale }; // no longer takes in to account the shadow
		if (messageWidthInPixels < boundingWidth) { boundingWidth = messageWidthInPixels; }

		// If no bounding box was specified, stay in the view.
		if (maxTilesPerRow == 0)
		{
			maxTilesPerRow = messageTileCount;
			boundingWidth = messageWidthInPixels;

			const int margin{ (borders || background ) ? box.margin : 0 };
			const int lineThickness{ (borders || background) ? box.lineThickness : 0 };
			const int edgeOffset{ margin + lineThickness + fontScale * 2 };

			// Bounds Right
			if (intify(startPosition.x) + messageWidthInPixels + edgeOffset > intify(getViewCoordinates(UR).x))
			{
				startPosition.x = floatify(getViewCoordinates(UR).x - messageWidthInPixels - edgeOffset);
			}
			// Bounds Left
			if (intify(startPosition.x) - edgeOffset < getViewCoordinates(UL).x)
			{
				startPosition.x = getViewCoordinates(UL).x + edgeOffset;
			}
			// Bounds Bottom
			if (intify(startPosition.y) + 8 * fontScale + edgeOffset > intify(getViewCoordinates(DR).y))
			{
				startPosition.y = floatify(getViewCoordinates(DR).y - (8 * fontScale) - edgeOffset);
			}
			// Bounds Top
			if (intify(startPosition.y) - edgeOffset < getViewCoordinates(UL).y)
			{
				startPosition.y = getViewCoordinates(UL).y + edgeOffset;
			}
		}
		while (messageTileCount % maxTilesPerRow != 0)
		{
			Font::currentString.push_back(78);
			messageTileCount += 1;
		}

		int messageRows{ messageTileCount / maxTilesPerRow };

		const int width{ boundingWidth + box.margin * 2 };
		// rows * 10 because text is 8 high plus 2 vertical gap. - 2 because no gap at the end.
		const int height{ messageRows * 10 * fontScale - 2 * fontScale + box.margin * 2 };
		const sf::Vector2f pos(pairF(startPosition.x - box.margin, startPosition.y - box.margin));

		if (background) { box.createBackground(pos, width, height); }
		if (borders) { box.createBorders(pos, width, height); }

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

