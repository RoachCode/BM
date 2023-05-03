#pragma once
#include "window.h"
#include "tilemap.h"

int main()
{
    Window window;




    TileMap tileMapA;
    tileMapA.setPosition(0.f, 0.f);
    tileMapA.createMasterTile
    (
        westKagar00a, westKagar10a, westKagar20a, westKagar30a,
        westKagar01a, westKagar11a, westKagar21a, westKagar31a,
        westKagar02a, westKagar12a, westKagar22a, westKagar32a,
        westKagar03a, westKagar13a, westKagar23a, westKagar33a
    );
    tileMapA.load(tileMapA.tileImage, sf::Vector2u(32, 32), 96, 56);
    
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);

    TileMap tileMapC;
    tileMapC.setPosition(0.f, 0.f);
    tileMapC.createMasterTile
    (
        westKagar00c, westKagar10c, westKagar20c, westKagar30c,
        westKagar01c, westKagar11c, westKagar21c, westKagar31c,
        westKagar02c, westKagar12c, westKagar22c, westKagar32c,
        westKagar03c, westKagar13c, westKagar23c, westKagar33c
    );
    tileMapC.load(tileMapC.tileImage, sf::Vector2u(32, 32), 96, 56);

    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);
    TileMap tileMapB;
    tileMapB.setPosition(0.f, 0.f);
    tileMapB.createMasterTile
    (
        westKagar00b, westKagar10b, westKagar20b, westKagar30b,
        westKagar01b, westKagar11b, westKagar21b, westKagar31b,
        westKagar02b, westKagar12b, westKagar22b, westKagar32b,
        westKagar03b, westKagar13b, westKagar23b, westKagar33b
    );
    tileMapB.load(tileMapB.tileImage, sf::Vector2u(32, 32), 96, 56);




	window.DEV_TOOLS.allowFreeMovement();
    window.font.setColor(sf::Color(155, 0, 0));
    while (window.isOpen())
    {
        window.clear();
        window.pollEvents();







        this->createMasterTile
        (
            westKagar00b, westKagar10b, westKagar20b, westKagar30b,
            westKagar01b, westKagar11b, westKagar21b, westKagar31b,
            westKagar02b, westKagar12b, westKagar22b, westKagar32b,
            westKagar03b, westKagar13b, westKagar23b, westKagar33b
        );
        this->createMasterTile
        (
            westKagar00c, westKagar10c, westKagar20c, westKagar30c,
            westKagar01c, westKagar11c, westKagar21c, westKagar31c,
            westKagar02c, westKagar12c, westKagar22c, westKagar32c,
            westKagar03c, westKagar13c, westKagar23c, westKagar33c
        );
        this->createMasterTile
        (
            westKagar00d, westKagar10d, westKagar20d, westKagar30d,
            westKagar01d, westKagar11d, westKagar21d, westKagar31d,
            westKagar02d, westKagar12d, westKagar22d, westKagar32d,
            westKagar03d, westKagar13d, westKagar23d, westKagar33d
        );
        this->createMasterTile
        (
            westKagar00e, westKagar10e, westKagar20e, westKagar30e,
            westKagar01e, westKagar11e, westKagar21e, westKagar31e,
            westKagar02e, westKagar12e, westKagar22e, westKagar32e,
            westKagar03e, westKagar13e, westKagar23e, westKagar33e
        );
        this->createMasterTile
        (
            westKagar00f, westKagar10f, westKagar20f, westKagar30f,
            westKagar01f, westKagar11f, westKagar21f, westKagar31f,
            westKagar02f, westKagar12f, westKagar22f, westKagar32f,
            westKagar03f, westKagar13f, westKagar23f, westKagar33f
        );
        this->createMasterTile
        (
            westKagar00g, westKagar10g, westKagar20g, westKagar30g,
            westKagar01g, westKagar11g, westKagar21g, westKagar31g,
            westKagar02g, westKagar12g, westKagar22g, westKagar32g,
            westKagar03g, westKagar13g, westKagar23g, westKagar33g
        );
        this->createMasterTile
        (
            westKagar00h, westKagar10h, westKagar20h, westKagar30h,
            westKagar01h, westKagar11h, westKagar21h, westKagar31h,
            westKagar02h, westKagar12h, westKagar22h, westKagar32h,
            westKagar03h, westKagar13h, westKagar23h, westKagar33h
        );
        this->createMasterTile
        (
            westKagar00i, westKagar10i, westKagar20i, westKagar30i,
            westKagar01i, westKagar11i, westKagar21i, westKagar31i,
            westKagar02i, westKagar12i, westKagar22i, westKagar32i,
            westKagar03i, westKagar13i, westKagar23i, westKagar33i
        );
        this->createMasterTile
        (
            westKagar00j, westKagar10j, westKagar20j, westKagar30j,
            westKagar01j, westKagar11j, westKagar21j, westKagar31j,
            westKagar02j, westKagar12j, westKagar22j, westKagar32j,
            westKagar03j, westKagar13j, westKagar23j, westKagar33j
        );




        window.draw(tileMap);

        window.drawText(window.DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
        window.display();

    }

    return 0;
}