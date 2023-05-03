#pragma once
#include "window.h"
#include "tilemap.h"
#include "devtools.h"

int main()
{
    Window window;
    TileMap tileMap;
    DevTools DEV_TOOLS;
    window.font.setColor(sf::Color(155, 0, 0));
    while (window.isOpen())
    {
        window.pollEvents();
        window.clear();

        //for (int i = 0; i < 160; i++)
        //{
            window.draw(tileMap);
        //}
        

        window.drawText(DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
        window.display();

    }

    return 0;
}