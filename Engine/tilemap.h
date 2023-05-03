#pragma once
#include <SFML/Graphics.hpp>
#include "maps.h"
#include "filesys.h"
#include "constExpressions.h"
// batching with vertex arrays / buffers?

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    sf::Image tileImage;
    void createMasterTile(
        unsigned short* a00, unsigned short* a10, unsigned short* a20, unsigned short* a30, 
        unsigned short* a01, unsigned short* a11, unsigned short* a21, unsigned short* a31, 
        unsigned short* a02, unsigned short* a12, unsigned short* a22, unsigned short* a32, 
        unsigned short* a03, unsigned short* a13, unsigned short* a23, unsigned short* a33
    );
    TileMap();
    bool load(const sf::Image& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<unsigned short> masterTile;
};