#pragma once
#include "tilemap.h"
// batching with vertex arrays / buffers?

bool TileMap::load(const unsigned short* tiles)
{
    // define parameters
    const sf::Image& tileImage = TileMap::tileImage;
    
    // load the tileset texture
    if (!m_tileset.loadFromImage(tileImage))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(TILES_PER_MAP_X * TILES_PER_MAP_Y * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < TILES_PER_MAP_X; ++i)
    {
        for (unsigned int j = 0; j < TILES_PER_MAP_Y; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * TILES_PER_MAP_X];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / TILE_SIZE);
            int tv = tileNumber / (m_tileset.getSize().x / TILE_SIZE);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * TILES_PER_MAP_X) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);

        }
    }
    return true;
}

TileMap::TileMap()
{
    tileImage.loadFromFile(getLocalPath() + "/ImageResources/TILE.bmp");
    tileImage.createMaskFromColor(sf::Color(237, 28, 36, 255), 0);
    tileImage.createMaskFromColor(sf::Color(13, 103, 148, 255), 150);
    tileImage.createMaskFromColor(sf::Color(26, 98, 138, 255), 200);

    //default load-in
    this->load(westKagar00a);
    this->setPosition(0.f, 0.f);
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
