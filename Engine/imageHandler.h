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
    sf::RectangleShape tilemapWindowBack;

    sf::RenderTexture tilemapRenderFront;
    sf::RectangleShape tilemapWindowFront;
    ImageHandler();

    void loadWestKagar();
    bool checkBounds(int direction, sf::Vector2i position);
};