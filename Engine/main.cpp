#pragma once
#include "window.h"
#include "tilemap.h"
#include "devtools.h"
#include <iostream>

int main()
{
    Window window;
    //window.setFramerateLimit(30);
    TileMap tileMap;
    DevTools DEV_TOOLS;

    while (window.isOpen())
    {
        window.pollEvents();
        window.clear();
        window.draw(tileMap);

        //DEV_TOOLS.showFPS();
        
        window.font.setColor(0, 0, 0);
        window.drawText("I FEEL SICK");
        window.display();

    }

    return 0;
}