#pragma once
#include "filesys.h"
#include "view.h"
#include "tilemap.h"
#include "maps.h"

class ImageHandler : public View
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

    sf::RenderTexture tilemapRenderBack;
    sf::RenderTexture tilemapRenderFront;
    
    sf::RectangleShape tilemapWindowBack;
    sf::RectangleShape tilemapWindowFront;

    ImageHandler();

    void loadWestKagar();
    bool checkBounds(int direction, sf::Vector2i position);
};