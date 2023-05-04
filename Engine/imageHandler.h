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
    sf::RectangleShape pseudoWindow;

    ImageHandler()
    {
        tileImage.loadFromFile(getLocalPath() + "/ImageResources/TILE.bmp");
        tileImage.createMaskFromColor(sf::Color(237, 28, 36, 255), 0);
        tileImage.createMaskFromColor(sf::Color(13, 103, 148, 255), 150);
        tileImage.createMaskFromColor(sf::Color(26, 98, 138, 255), 200);

        tilemapVector.push_back(&tileMapA);
        tilemapVector.push_back(&tileMapB);
        tilemapVector.push_back(&tileMapC);
        tilemapVector.push_back(&tileMapD);
        tilemapVector.push_back(&tileMapE);
        tilemapVector.push_back(&tileMapF);
        tilemapVector.push_back(&tileMapG);
        tilemapVector.push_back(&tileMapH);
        tilemapVector.push_back(&tileMapI);
        tilemapVector.push_back(&tileMapJ);



        renderWindow.create(32 * 24 * 4, 32 * 14 * 4);
        renderWindow.clear(sf::Color(255, 0, 0, 255));
        pseudoWindow.setSize(sf::Vector2f(32 * 24 * 4, 32 * 14 * 4));
        //renderTexture.create(32 * 24 * 4, 32 * 14 * 4);

        this->loadWestKagar();

    }

    void loadWestKagar()
    {

        for (int i = 0; i < tilemapVector.size(); i++)
        {
            switch (i)
            {
            case 0:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00a, westKagar10a, westKagar20a, westKagar30a,
                    westKagar01a, westKagar11a, westKagar21a, westKagar31a,
                    westKagar02a, westKagar12a, westKagar22a, westKagar32a,
                    westKagar03a, westKagar13a, westKagar23a, westKagar33a
                );
                break;
            case 1:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00b, westKagar10b, westKagar20b, westKagar30b,
                    westKagar01b, westKagar11b, westKagar21b, westKagar31b,
                    westKagar02b, westKagar12b, westKagar22b, westKagar32b,
                    westKagar03b, westKagar13b, westKagar23b, westKagar33b
                );
                break;
            case 2:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00c, westKagar10c, westKagar20c, westKagar30c,
                    westKagar01c, westKagar11c, westKagar21c, westKagar31c,
                    westKagar02c, westKagar12c, westKagar22c, westKagar32c,
                    westKagar03c, westKagar13c, westKagar23c, westKagar33c
                );
                break;
            case 3:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00d, westKagar10d, westKagar20d, westKagar30d,
                    westKagar01d, westKagar11d, westKagar21d, westKagar31d,
                    westKagar02d, westKagar12d, westKagar22d, westKagar32d,
                    westKagar03d, westKagar13d, westKagar23d, westKagar33d
                );
                break;
            case 4:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00e, westKagar10e, westKagar20e, westKagar30e,
                    westKagar01e, westKagar11e, westKagar21e, westKagar31e,
                    westKagar02e, westKagar12e, westKagar22e, westKagar32e,
                    westKagar03e, westKagar13e, westKagar23e, westKagar33e
                );
                break;
            case 5:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00f, westKagar10f, westKagar20f, westKagar30f,
                    westKagar01f, westKagar11f, westKagar21f, westKagar31f,
                    westKagar02f, westKagar12f, westKagar22f, westKagar32f,
                    westKagar03f, westKagar13f, westKagar23f, westKagar33f
                );
                break;
            case 6:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00g, westKagar10g, westKagar20g, westKagar30g,
                    westKagar01g, westKagar11g, westKagar21g, westKagar31g,
                    westKagar02g, westKagar12g, westKagar22g, westKagar32g,
                    westKagar03g, westKagar13g, westKagar23g, westKagar33g
                );
                break;
            case 7:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00h, westKagar10h, westKagar20h, westKagar30h,
                    westKagar01h, westKagar11h, westKagar21h, westKagar31h,
                    westKagar02h, westKagar12h, westKagar22h, westKagar32h,
                    westKagar03h, westKagar13h, westKagar23h, westKagar33h
                );
                break;
            case 8:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00i, westKagar10i, westKagar20i, westKagar30i,
                    westKagar01i, westKagar11i, westKagar21i, westKagar31i,
                    westKagar02i, westKagar12i, westKagar22i, westKagar32i,
                    westKagar03i, westKagar13i, westKagar23i, westKagar33i
                );
                break;
            case 9:
                tilemapVector[i]->createMasterTile
                (
                    westKagar00j, westKagar10j, westKagar20j, westKagar30j,
                    westKagar01j, westKagar11j, westKagar21j, westKagar31j,
                    westKagar02j, westKagar12j, westKagar22j, westKagar32j,
                    westKagar03j, westKagar13j, westKagar23j, westKagar33j
                );
                break;
            default:
                break;
            }

            tilemapVector[i]->load(tileImage, sf::Vector2u(32, 32), 96, 56);
            renderWindow.draw(*tilemapVector[i]);
        }
        renderWindow.display();
        //const sf::Texture& renderTexture = ;
        pseudoWindow.setTexture(&renderWindow.getTexture());
    }

};