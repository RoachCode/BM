#pragma once
#include "window.h"
#include "tilemap.h"
#include "devtools.h"

void drawTileMap()
{

}

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

		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00b, westKagar10b, westKagar20b, westKagar30b,
			westKagar01b, westKagar11b, westKagar21b, westKagar31b,
			westKagar02b, westKagar12b, westKagar22b, westKagar32b,
			westKagar03b, westKagar13b, westKagar23b, westKagar33b
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00c, westKagar10c, westKagar20c, westKagar30c,
			westKagar01c, westKagar11c, westKagar21c, westKagar31c,
			westKagar02c, westKagar12c, westKagar22c, westKagar32c,
			westKagar03c, westKagar13c, westKagar23c, westKagar33c
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00d, westKagar10d, westKagar20d, westKagar30d,
			westKagar01d, westKagar11d, westKagar21d, westKagar31d,
			westKagar02d, westKagar12d, westKagar22d, westKagar32d,
			westKagar03d, westKagar13d, westKagar23d, westKagar33d
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00e, westKagar10e, westKagar20e, westKagar30e,
			westKagar01e, westKagar11e, westKagar21e, westKagar31e,
			westKagar02e, westKagar12e, westKagar22e, westKagar32e,
			westKagar03e, westKagar13e, westKagar23e, westKagar33e
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00f, westKagar10f, westKagar20f, westKagar30f,
			westKagar01f, westKagar11f, westKagar21f, westKagar31f,
			westKagar02f, westKagar12f, westKagar22f, westKagar32f,
			westKagar03f, westKagar13f, westKagar23f, westKagar33f
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00g, westKagar10g, westKagar20g, westKagar30g,
			westKagar01g, westKagar11g, westKagar21g, westKagar31g,
			westKagar02g, westKagar12g, westKagar22g, westKagar32g,
			westKagar03g, westKagar13g, westKagar23g, westKagar33g
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00h, westKagar10h, westKagar20h, westKagar30h,
			westKagar01h, westKagar11h, westKagar21h, westKagar31h,
			westKagar02h, westKagar12h, westKagar22h, westKagar32h,
			westKagar03h, westKagar13h, westKagar23h, westKagar33h
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00i, westKagar10i, westKagar20i, westKagar30i,
			westKagar01i, westKagar11i, westKagar21i, westKagar31i,
			westKagar02i, westKagar12i, westKagar22i, westKagar32i,
			westKagar03i, westKagar13i, westKagar23i, westKagar33i
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);
		tileMap.createMasterTile
		(
			westKagar00j, westKagar10j, westKagar20j, westKagar30j,
			westKagar01j, westKagar11j, westKagar21j, westKagar31j,
			westKagar02j, westKagar12j, westKagar22j, westKagar32j,
			westKagar03j, westKagar13j, westKagar23j, westKagar33j
		);
		tileMap.load(tileMap.tileImage, sf::Vector2u(32, 32), 96, 56);
		window.draw(tileMap);

        window.drawText(DEV_TOOLS.getFPS(), sf::Vector2f(10000, 50));
        window.display();

    }

    return 0;
}