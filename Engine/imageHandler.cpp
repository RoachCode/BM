#pragma once
#include "imageHandler.h"

ImageHandler::ImageHandler()
{
    zDepth = 10;

    back.lightShader.loadFromMemory(lightFrag, sf::Shader::Fragment);
    back.normalShader.loadFromMemory(normalsFrag, sf::Shader::Fragment);
    front.lightShader.loadFromMemory(lightFrag, sf::Shader::Fragment);
    front.normalShader.loadFromMemory(normalsFrag, sf::Shader::Fragment);

    if (!tileImage.loadFromFile("C:/Users/Windows/Documents/Github/Broken Mirror v2/BM/ImageResources/TILE.bmp"))
    {
        tileImage.loadFromFile(getLocalPath() + "../ImageResources/TILE.bmp");
    }
    tileImage.createMaskFromColor(sf::Color(237, 28, 36, 255), 0);
    tileImage.createMaskFromColor(sf::Color(13, 103, 148, 255), 150);
    tileImage.createMaskFromColor(sf::Color(26, 98, 138, 255), 200);

    if (!tileNormalImage.loadFromFile("C:/Users/Windows/Documents/Github/Broken Mirror v2/BM/ImageResources/TILE-NORMAL.bmp"))
    {
        tileNormalImage.loadFromFile(getLocalPath() + "../ImageResources/TILE-NORMAL.bmp");
    }
    tileNormalImage.createMaskFromColor(sf::Color(255, 255, 255, 255), 0);

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

    tilemapNormalVector.push_back(&tileMapNormalA);
    tilemapNormalVector.push_back(&tileMapNormalB);
    tilemapNormalVector.push_back(&tileMapNormalC);
    tilemapNormalVector.push_back(&tileMapNormalD);
    tilemapNormalVector.push_back(&tileMapNormalE);
    tilemapNormalVector.push_back(&tileMapNormalF);
    tilemapNormalVector.push_back(&tileMapNormalG);
    tilemapNormalVector.push_back(&tileMapNormalH);
    tilemapNormalVector.push_back(&tileMapNormalI);
    tilemapNormalVector.push_back(&tileMapNormalJ);

    sf::Vector2u sceneSize = View::getSceneSize();

    back.tilemapRender.create(intify(sceneSize.x), intify(sceneSize.y));
    back.normalRender.create(intify(sceneSize.x), intify(sceneSize.y));
    back.sceneRender.create(intify(sceneSize.x), intify(sceneSize.y));
    front.tilemapRender.create(intify(sceneSize.x), intify(sceneSize.y));
    front.normalRender.create(intify(sceneSize.x), intify(sceneSize.y));
    front.sceneRender.create(intify(sceneSize.x), intify(sceneSize.y));

    back.lightRender.create(View::getScreenSize().x, View::getScreenSize().y);
    front.lightRender.create(View::getScreenSize().x, View::getScreenSize().y);

    this->loadWestKagar();
}

void ImageHandler::loadWestKagar()
{
    back.sceneRender.clear();
    back.tilemapRender.clear();
    back.normalRender.clear();
    front.sceneRender.clear(sf::Color::Transparent);
    front.tilemapRender.clear(sf::Color::Transparent);
    front.normalRender.clear();

    tilemapVector.clear();
    tilemapNormalVector.clear();

    for (int i = 0; i < zDepth; i++)
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
            tilemapNormalVector[i]->createMasterTile
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
        tilemapNormalVector[i]->load(tileNormalImage, sf::Vector2u(32, 32), 96, 56);

        if (i < 5)
        {
            back.tilemapRender.draw(*tilemapVector[i]);
            back.normalRender.draw(*tilemapNormalVector[i]);
        }
        else
        {
            front.tilemapRender.draw(*tilemapVector[i]);
            front.normalRender.draw(*tilemapNormalVector[i]);
        }
    }

    back.normalRender.display();
    back.tilemapRender.display();
    front.normalRender.display();
    front.tilemapRender.display();

    this->loadLights(back);
    this->loadLights(front);
}

void ImageHandler::loadLights(RenderPipeline &scene)
{
    int width{ intify(View::getSceneSize().x * View::getPixelSize()) };
    int height{ intify(View::getSceneSize().y * View::getPixelSize()) };

    scene.lightRender.clear();

    scene.pass_normals.create(width, height);
    scene.pass_normals.clear(sf::Color(128, 128, 255));

    // Get textures, entire scene
    scene.normal_map = scene.normalRender.getTexture();
    scene.diffuse_map = scene.tilemapRender.getTexture();

    // Draw diffuse map to normals pass with normals shader
    sf::RenderStates states;
    states.transform.scale(pairF(View::getPixelSize(), View::getPixelSize()));
    states.shader = &scene.normalShader;
    scene.normalShader.setUniform("sampler_normal", scene.normal_map);
    scene.pass_normals.draw(sf::Sprite(scene.diffuse_map), states);
    scene.pass_normals.display();

    // Light Pass, renders every light into a rendertexture
    scene.lightShader.setUniform("resolution", sf::Vector2f(View::getScreenSize().x, View::getScreenSize().y));
    scene.lightShader.setUniform("sampler_light", scene.lightRender.getTexture());
    scene.lightShader.setUniform("ambient_intensity", scene.light.ambientIntensity);
    scene.lightShader.setUniform("falloff", scene.light.falloff);
    scene.lightShader.setUniform("light_color", scene.light.color);
    scene.lightShader.setUniform("sampler_normal", scene.pass_normals.getTexture());

    scene.tilemapRenderSprite.setTexture(scene.tilemapRender.getTexture());

}

void ImageHandler::drawScene(RenderPipeline& scene)
{
    // Clear render and draw diffuse scene
    scene.sceneRender.clear(sf::Color::Transparent);
    scene.sceneRender.draw(scene.tilemapRenderSprite);

    // Draw light shader over diffuse scene, blended
    sf::RenderStates renderStates;
    renderStates.blendMode = sf::BlendMultiply;
    renderStates.shader = &scene.lightShader;
    scene.sceneRender.draw(scene.tilemapRenderSprite, renderStates);

    // Display scene
    scene.sceneRender.display();
}

// Checks the lowest map for allowable movement.
bool ImageHandler::checkBounds(int direction, sf::Vector2i gridPosition)
{
    bool allowed{ false };
    switch (direction)
    {
    case UP:
        (tileMapA.masterTile[(gridPosition.y - 1) * (4 * TILES_PER_CHUNK_X) + gridPosition.x]) == 0 ? allowed = true : allowed = false;
        break;
    case DOWN:
        (tileMapA.masterTile[(gridPosition.y + 1) * (4 * TILES_PER_CHUNK_X) + gridPosition.x]) == 0 ? allowed = true : allowed = false;
        break;
    case LEFT:
        (tileMapA.masterTile[gridPosition.y * (4 * TILES_PER_CHUNK_X) + gridPosition.x - 1]) == 0 ? allowed = true : allowed = false;
        break;
    case RIGHT:
        (tileMapA.masterTile[gridPosition.y * (4 * TILES_PER_CHUNK_X) + gridPosition.x + 1]) == 0 ? allowed = true : allowed = false;
        break;
    default:
        break;
    }
    return allowed;
}