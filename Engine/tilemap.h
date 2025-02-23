#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    void createMasterTile(
        unsigned short* a00, unsigned short* a10, unsigned short* a20, unsigned short* a30,
        unsigned short* a01, unsigned short* a11, unsigned short* a21, unsigned short* a31,
        unsigned short* a02, unsigned short* a12, unsigned short* a22, unsigned short* a32,
        unsigned short* a03, unsigned short* a13, unsigned short* a23, unsigned short* a33
    );
    TileMap();
    bool load(const sf::Image& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
    std::vector<unsigned short> masterTile;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

class FontMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const sf::Image& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};