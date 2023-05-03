#pragma once
#include "tilemap.h"
#include <iostream>
// batching with vertex arrays / buffers?



bool TileMap::load(const sf::Image& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromImage(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = masterTile[i + j * width];

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

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}


TileMap::TileMap()
{
    //default load-in
    this->setPosition(0.f, 0.f);
}

void TileMap::createMasterTile(
    unsigned short* a00, unsigned short* a10, unsigned short* a20, unsigned short* a30,
    unsigned short* a01, unsigned short* a11, unsigned short* a21, unsigned short* a31,
    unsigned short* a02, unsigned short* a12, unsigned short* a22, unsigned short* a32,
    unsigned short* a03, unsigned short* a13, unsigned short* a23, unsigned short* a33
)
{
    masterTile.clear();

    // 4 x 4 tilesets...
    for (int y = 0; y < 14; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a00[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a10[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a20[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a30[x + y * 24]);
        }
    }
    for (int y = 0; y < 14; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a01[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a11[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a21[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a31[x + y * 24]);
        }
    }
    for (int y = 0; y < 14; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a02[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a12[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a22[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a32[x + y * 24]);
        }
    }
    for (int y = 0; y < 14; y++)
    {
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a03[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a13[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a23[x + y * 24]);
        }
        for (int x = 0; x < 24; x++)
        {
            masterTile.push_back(a33[x + y * 24]);
        }
    }
}