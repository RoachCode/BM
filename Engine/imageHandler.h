#pragma once
#include "filesys.h"
#include "tilemap.h"
#include "maps.h"

class ImageHandler
{
public:
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

    sf::RenderTexture renderWindow;
    sf::RenderTexture renderWindow2;
    sf::RectangleShape pseudoWindow;
    sf::RectangleShape pseudoWindow2;

    ImageHandler();

    void loadWestKagar();

};