#pragma once
#include "filesys.h"
#include "tilemap.h"
#include "maps.h"

class ImageHandler
{
public:
    uint8_t zDepth;
    TileMap tileMapA;
    TileMap tileMapB;
    TileMap tileMapC;
    TileMap tileMapD;
    TileMap tileMapE;
    TileMap tileMapF;
    TileMap tileMapG;
    TileMap tileMapH;
    TileMap tileMapI;
    TileMap tileMapJ;
    sf::Image tileImage;
    std::vector<TileMap*> tilemapVector;
    sf::Vector2u sceneSize;

    sf::RenderTexture tilemapRenderBack;
    sf::RenderTexture tilemapRenderFront;
    sf::RenderTexture tempRender;
    sf::RectangleShape tempRectangle;
    
    sf::RectangleShape tilemapWindowBack;
    sf::RectangleShape tilemapWindowFront;

    sf::CircleShape circle;
    int iterator;
    bool transparency;

    ImageHandler();

    void loadWestKagar();
    bool checkBounds(int direction, sf::Vector2i position);
    void transparencyToggle();
};