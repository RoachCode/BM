#pragma once
#include "window.h"
#include "tilemap.h"
#include "devtools.h"

int main()
{
    Window window;
    TileMap tileMap;
    DevTools DEV_TOOLS;

    while (window.isOpen())
    {
        window.pollEvents();
        window.clear();
        window.draw(tileMap);

        //DEV_TOOLS.getFPS(); gotta get numbers done before I can print numbers!
        
        window.drawText(DEV_TOOLS.getFPS());
        window.display();

    }

    return 0;
}