#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "view.h"

class TextBox : public View
{
private:
public:
    sf::Sprite corner;
    sf::Texture cornerTexture;
    std::vector<bool> cornerArray
    {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    };
    sf::RectangleShape border;
    sf::VertexArray background;

    sf::Color topLeft;
    sf::Color topRight;
    sf::Color bottomRight;
    sf::Color bottomLeft;
    sf::Color borderColor;

    TextBox()
    {
        borderColor = sf::Color::White;
        createCorner();
        topLeft = sf::Color(0, 0, 255, 50);
        topRight = sf::Color(0, 0, 255, 50);
        bottomRight = sf::Color(0, 0, 255, 50);
        bottomLeft = sf::Color(0, 0, 255, 50);
    }

    void createFullscreenBackground(int x, int y, int width, int height)
    {
        background.setPrimitiveType(sf::Quads);
        background[0].position = pairF(x, y);
        background[1].position = pairF(x + width, y);
        background[2].position = pairF(x + width, y + height);
        background[3].position = pairF(x, y + height);

        background[0].color = topLeft;
        background[1].color = topRight;
        background[2].color = bottomRight;
        background[3].color = bottomLeft;
    }

    void createCorner()
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



};