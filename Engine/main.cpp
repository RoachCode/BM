#pragma once
#include "../Engine/window.h"
#include <filesystem>
#include <iostream>
#include "filesys.h"
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const sf::Image& tileImage, sf::Vector2u tileSize, const unsigned short* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromImage(tileImage))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

            }
        }
        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

int main()
{
    const std::string LOCAL_PATH = std::filesystem::current_path().string();

    Window window;

    unsigned short mapArray[] =
    {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 25, 25, 13, 13, 13, 0, 0, 0, 0, 0, 28, 20, 20, 20, 20, 20, 20, 20,
    0, 0, 0, 25, 25, 25, 25, 0, 0, 84, 13, 0, 0, 0, 0, 28, 31, 90, 90, 90, 90, 90, 90, 90,
    11, 25, 25, 28, 20, 20, 20, 20, 20, 20, 13, 20, 20, 20, 20, 31, 90, 89, 89, 89, 89, 89, 89, 89,
    20, 20, 20, 31, 90, 90, 90, 90, 90, 90, 18, 90, 90, 90, 90, 90, 89, 89, 89, 89, 89, 89, 89, 89,
    90, 90, 90, 90, 89, 89, 89, 89, 89, 89, 18, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
    89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 18, 89, 89, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    89, 89, 6, 2, 2, 2, 2, 2, 2, 2, 15, 2, 2, 29, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0,
    2, 2, 29, 0, 0, 0, 0, 0, 0, 25, 13, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 87, 4, 4, 4, 4, 4, 4,
    11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 86, 0, 0, 0, 87, 85, 4, 4, 85, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 4, 4, 4, 4, 4, 4, 4, 4, 85, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 4, 4, 13, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 168, 169, 168, 169, 170, 168, 168, 169, 170, 168, 168, 169, 169, 168, 168,

    };

    sf::Image tileImage;
    TileMap tileMap;
    //tileImage.loadFromFile("C:/TileMaster/TILE.bmp");
    tileImage.loadFromFile(LOCAL_PATH + "/ImageRes/TILE.bmp");
    tileImage.createMaskFromColor(sf::Color(237, 28, 36, 255), 0);
    tileImage.createMaskFromColor(sf::Color(13, 103, 148, 255), 150);
    tileImage.createMaskFromColor(sf::Color(26, 98, 138, 255), 200);
    
    tileMap.load(tileImage, sf::Vector2u(32, 32), mapArray, 24, 14);
    tileMap.setPosition(0.f, 0.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                    window.close();
                    break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}