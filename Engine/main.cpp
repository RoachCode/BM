#pragma once
#include "window.h"
#include "filesys.h"
#include "maps.h"
#include "tilemap.h"
#include "events.h"

int main()
{
    Window window;
    TileMap tileMap;

    sf::Image tileImage;

    tileImage.loadFromFile(getLocalPath() + "/ImageResources/TILE.bmp");
    tileImage.createMaskFromColor(sf::Color(237, 28, 36, 255), 0);
    tileImage.createMaskFromColor(sf::Color(13, 103, 148, 255), 150);
    tileImage.createMaskFromColor(sf::Color(26, 98, 138, 255), 200);

    //default load-in
    tileMap.load(tileImage, sf::Vector2u(32, 32), mapArray, 24, 14);
    tileMap.setPosition(0.f, 0.f);

    while (window.isOpen())
    {
        //pollEvents();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                    window.close();
                    break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}