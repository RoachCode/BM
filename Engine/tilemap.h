#pragma once
#include <SFML/Graphics.hpp>
#include "maps.h"
#include "filesys.h"
#include "constExpressions.h"
// batching with vertex arrays / buffers?

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    bool load(const unsigned short* tiles);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Image tileImage;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};