#pragma once
#include "window.h"
#include "tilemap.h"
#include "devtools.h"
#include "font.h"
#include <iostream>

int main()
{
    Window window;
    //window.setFramerateLimit(30);
    TileMap tileMap;
    DevTools DEV_TOOLS;
    Font font;

    while (window.isOpen())
    {
        window.pollEvents();
        window.clear();
        window.draw(tileMap);

        DEV_TOOLS.showFPS();
        
        window.draw(font.A);
        window.display();

    }

    return 0;
}