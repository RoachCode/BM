#pragma once
#include "window.h"
#include "tilemap.h"

int main()
{
    Window window;
    TileMap tileMap;
    
    while (window.isOpen())
    {
        window.pollEvents();
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}