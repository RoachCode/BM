#pragma once
#include "character.h"
#include "view.h"

// CharacterSprite
// Public
void CharacterSprite::buildTextureAtlas()
{

}

CharacterSprite::CharacterSprite(int id) : m_id(id)
{
    // Define sprite size
    width = TILE_SIZE;
    height = TILE_SIZE;

    // Load shaders
    colorShader.loadFromMemory(colorFrag, sf::Shader::Fragment);
    outlineShader.loadFromMemory(outlineFrag, sf::Shader::Fragment);
    invertShader.loadFromMemory(invertFrag, sf::Shader::Fragment);
    colorShader.setUniform("texture", sf::Shader::CurrentTexture);
    outlineShader.setUniform("texture", sf::Shader::CurrentTexture);
    invertShader.setUniform("texture", sf::Shader::CurrentTexture);

    // Set sprite color (shader) and other renderstates
    setSpriteShader();
    shaderSprite.sprite.setScale(pairF(View::getPixelSize(), View::getPixelSize()));

    // Set sprite texture (with animation flag boolean)
    m_clearBools();
    textureUpdate(animFlag.downABool);

}
void CharacterSprite::setSpriteShader(SpriteColor colorEnum)
{
    spriteColor = colorEnum;
    switch (colorEnum)
    {
    case SpriteColor::Default:
        colorShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(255, 255, 255, 255)));
        shaderSprite.renderStates.shader = &colorShader;
        break;
    case SpriteColor::Blue:
        colorShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(20, 150, 255, 255)));
        shaderSprite.renderStates.shader = &colorShader;
        break;
    case SpriteColor::Transparent:
        colorShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(255, 255, 255, 128)));
        shaderSprite.renderStates.shader = &colorShader;
        break;
    case SpriteColor::Dark:
        outlineShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(-255, -255, -255, 255)));
        shaderSprite.renderStates.shader = &outlineShader;
        break;
    case SpriteColor::Black:
        colorShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(0, 0, 0, 255)));
        shaderSprite.renderStates.shader = &colorShader;
        break;
    case SpriteColor::Inverted:
        shaderSprite.renderStates.shader = &invertShader;
        break;
    case SpriteColor::Outline:
        shaderSprite.renderStates.shader = &outlineShader;
        break;
    default:
        colorShader.setUniform("colorIn", sf::Glsl::Vec4(sf::Color(255, 255, 255, 255)));
        shaderSprite.renderStates.shader = &colorShader;
        break;
    }
}
void CharacterSprite::textureUpdate()
{
    texture.create(width, height);
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];

    uint8_t rw{ 255 };
    uint8_t gw{ 0 };
    uint8_t bw{ 0 };
    uint8_t aw{ 255 };

    for (int i = 0; i < width * height * 4; i += 4)
    {
        rw = currentTextureVector[0 + i];
        gw = currentTextureVector[1 + i];
        bw = currentTextureVector[2 + i];
        aw = currentTextureVector[3 + i];

        pixels[i + 0] = rw;
        pixels[i + 1] = gw;
        pixels[i + 2] = bw;
        pixels[i + 3] = aw;
    }
    texture.update(pixels);
    shaderSprite.sprite.setTexture(texture);

    delete[] pixels;
    currentTextureVector.clear();
}
void CharacterSprite::textureUpdate(bool& inputBool)
{
    m_clearBools();
    inputBool = true;
    pickArray();
    textureUpdate();
}
void CharacterSprite::pickArray()
{
    // Copies the correct texture array to the currentTextureVector stack.
    switch (m_id)
    {
    case 0:
        break;
    case 1: // Arson
        for (unsigned int i = 0; i < arsonDownA.size(); i++)
        { // Arson
            if (animFlag.downABool) { currentTextureVector.push_back(arsonDownA[i]); }
            else if (animFlag.downBBool) { currentTextureVector.push_back(arsonDownB[i]); }
            else if (animFlag.downCBool) { currentTextureVector.push_back(arsonDownC[i]); }
            else if (animFlag.upABool) { currentTextureVector.push_back(arsonUpA[i]); }
            else if (animFlag.upBBool) { currentTextureVector.push_back(arsonUpB[i]); }
            else if (animFlag.upCBool) { currentTextureVector.push_back(arsonUpC[i]); }
            else if (animFlag.leftABool) { currentTextureVector.push_back(arsonLeftA[i]); }
            else if (animFlag.leftBBool) { currentTextureVector.push_back(arsonLeftB[i]); }
            else if (animFlag.leftCBool) { currentTextureVector.push_back(arsonLeftC[i]); }
            else if (animFlag.rightABool) { currentTextureVector.push_back(arsonRightA[i]); }
            else if (animFlag.rightBBool) { currentTextureVector.push_back(arsonRightB[i]); }
            else if (animFlag.rightCBool) { currentTextureVector.push_back(arsonRightC[i]); }
            else if (animFlag.frontBool) { currentTextureVector.push_back(arsonFront[i]); }
            else if (animFlag.backBool) { currentTextureVector.push_back(arsonBack[i]); }
            else if (animFlag.idleLBool) { currentTextureVector.push_back(arsonIdleL[i]); }
            else if (animFlag.idleRBool) { currentTextureVector.push_back(arsonIdleR[i]); }
            else if (animFlag.shrug1RBool) { currentTextureVector.push_back(arsonShrug1R[i]); }
            else if (animFlag.shrug1LBool) { currentTextureVector.push_back(arsonShrug1L[i]); }
            else if (animFlag.shrug2RBool) { currentTextureVector.push_back(arsonShrug2R[i]); }
            else if (animFlag.shrug2LBool) { currentTextureVector.push_back(arsonShrug2L[i]); }
            else if (animFlag.shrug2mouthRBool) { currentTextureVector.push_back(arsonShrug2mouthR[i]); }
            else if (animFlag.shrug2mouthLBool) { currentTextureVector.push_back(arsonShrug2mouthL[i]); }
            else if (animFlag.crawlRBool) { currentTextureVector.push_back(arsonCrawlR[i]); }
            else if (animFlag.crawlLBool) { currentTextureVector.push_back(arsonCrawlL[i]); }
            else if (animFlag.pointRBool) { currentTextureVector.push_back(arsonPointR[i]); }
            else if (animFlag.pointLBool) { currentTextureVector.push_back(arsonPointL[i]); }
            else if (animFlag.handsUpRBool) { currentTextureVector.push_back(arsonHandsUpR[i]); }
            else if (animFlag.handsUpLBool) { currentTextureVector.push_back(arsonHandsUpL[i]); }
            else if (animFlag.pushRBool) { currentTextureVector.push_back(arsonPushR[i]); }
            else if (animFlag.pushLBool) { currentTextureVector.push_back(arsonPushL[i]); }
            else if (animFlag.deadRBool) { currentTextureVector.push_back(arsonDeadR[i]); }
            else if (animFlag.deadLBool) { currentTextureVector.push_back(arsonDeadL[i]); }
            else if (animFlag.hitRBool) { currentTextureVector.push_back(arsonHitR[i]); }
            else if (animFlag.hitLBool) { currentTextureVector.push_back(arsonHitL[i]); }
        }
        break;
    case 2: // Gaia
        if (animFlag.rightABool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(gaiaLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(gaiaLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(gaiaLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(gaiaLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.rightBBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(gaiaLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(gaiaLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(gaiaLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(gaiaLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
            break;
        }
        else if (animFlag.rightCBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(gaiaLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(gaiaLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(gaiaLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(gaiaLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.idleRBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(gaiaIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(gaiaIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(gaiaIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(gaiaIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < gaiaDownA.size(); i++)
            {
                if (animFlag.downABool) { currentTextureVector.push_back(gaiaDownA[i]); }
                else if (animFlag.downBBool) { currentTextureVector.push_back(gaiaDownB[i]); }
                else if (animFlag.downCBool) { currentTextureVector.push_back(gaiaDownC[i]); }
                else if (animFlag.upABool) { currentTextureVector.push_back(gaiaUpA[i]); }
                else if (animFlag.upBBool) { currentTextureVector.push_back(gaiaUpB[i]); }
                else if (animFlag.upCBool) { currentTextureVector.push_back(gaiaUpC[i]); }
                else if (animFlag.leftABool) { currentTextureVector.push_back(gaiaLeftA[i]); }
                else if (animFlag.leftBBool) { currentTextureVector.push_back(gaiaLeftB[i]); }
                else if (animFlag.leftCBool) { currentTextureVector.push_back(gaiaLeftC[i]); }
                else if (animFlag.frontBool) { currentTextureVector.push_back(gaiaFront[i]); }
                else if (animFlag.backBool) { currentTextureVector.push_back(gaiaBack[i]); }
                else if (animFlag.idleLBool) { currentTextureVector.push_back(gaiaIdleL[i]); }
            }
        }
        break;
    case 3: // Cole 
        if (animFlag.rightABool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(coleLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(coleLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(coleLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(coleLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.rightBBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(coleLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(coleLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(coleLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(coleLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
            break;
        }
        else if (animFlag.rightCBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(coleLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(coleLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(coleLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(coleLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.idleRBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(coleIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(coleIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(coleIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(coleIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < coleDownA.size(); i++)
            {
                if (animFlag.downABool) { currentTextureVector.push_back(coleDownA[i]); }
                else if (animFlag.downBBool) { currentTextureVector.push_back(coleDownB[i]); }
                else if (animFlag.downCBool) { currentTextureVector.push_back(coleDownC[i]); }
                else if (animFlag.upABool) { currentTextureVector.push_back(coleUpA[i]); }
                else if (animFlag.upBBool) { currentTextureVector.push_back(coleUpB[i]); }
                else if (animFlag.upCBool) { currentTextureVector.push_back(coleUpC[i]); }
                else if (animFlag.leftABool) { currentTextureVector.push_back(coleLeftA[i]); }
                else if (animFlag.leftBBool) { currentTextureVector.push_back(coleLeftB[i]); }
                else if (animFlag.leftCBool) { currentTextureVector.push_back(coleLeftC[i]); }
                else if (animFlag.frontBool) { currentTextureVector.push_back(coleFront[i]); }
                else if (animFlag.backBool) { currentTextureVector.push_back(coleBack[i]); }
                else if (animFlag.idleLBool) { currentTextureVector.push_back(coleIdleL[i]); }
            }
        }
        break;
    case 4: // Neko
        if (animFlag.rightABool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(nekoLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(nekoLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(nekoLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(nekoLeftA[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.rightBBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(nekoLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(nekoLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(nekoLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(nekoLeftB[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
            break;
        }
        else if (animFlag.rightCBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(nekoLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(nekoLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(nekoLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(nekoLeftC[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else if (animFlag.idleRBool)
        {
            for (int k = 0; k < TILE_SIZE; k++) // vertical count
            {
                for (int j = 0; j < 4 * TILE_SIZE; j += 4)
                {
                    currentTextureVector.push_back(nekoIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 3]);
                    currentTextureVector.push_back(nekoIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 2]);
                    currentTextureVector.push_back(nekoIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j - 1]);
                    currentTextureVector.push_back(nekoIdleL[(k * TILE_SIZE * 4) + (4 * TILE_SIZE) - 1 - j]);
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < nekoDownA.size(); i++)
            {
                if (animFlag.downABool) { currentTextureVector.push_back(nekoDownA[i]); }
                else if (animFlag.downBBool) { currentTextureVector.push_back(nekoDownB[i]); }
                else if (animFlag.downCBool) { currentTextureVector.push_back(nekoDownC[i]); }
                else if (animFlag.upABool) { currentTextureVector.push_back(nekoUpA[i]); }
                else if (animFlag.upBBool) { currentTextureVector.push_back(nekoUpB[i]); }
                else if (animFlag.upCBool) { currentTextureVector.push_back(nekoUpC[i]); }
                else if (animFlag.leftABool) { currentTextureVector.push_back(nekoLeftA[i]); }
                else if (animFlag.leftBBool) { currentTextureVector.push_back(nekoLeftB[i]); }
                else if (animFlag.leftCBool) { currentTextureVector.push_back(nekoLeftC[i]); }
                else if (animFlag.frontBool) { currentTextureVector.push_back(nekoFront[i]); }
                else if (animFlag.backBool) { currentTextureVector.push_back(nekoBack[i]); }
                else if (animFlag.idleLBool) { currentTextureVector.push_back(nekoIdleL[i]); }
            }
        }
        break;
    default:
        break;
    }
}
void CharacterSprite::changeAnimationState(int x, int y, int pixelSize)
{
    const sf::Vector2f grid{
        shaderSprite.sprite.getPosition().x / (TILE_SIZE * pixelSize),
        shaderSprite.sprite.getPosition().y / (TILE_SIZE * pixelSize)
    };
    //std::cout << std::to_string(sprite.getGlobalBounds().height * sprite.getScale().x) << '\n';
    // West Kagar Ladders
    // todo: Add more codes perhaps, and more animation choices to the switch? y = -2, etc.
    // maybe make a function that works in all directions. Call it moonwalk()
    if (grid.x == 7)
    {
        if (grid.y > 32 && grid.y <= 37)
        {
            y = -1;
        }
    }
    else if (grid.x == 9)
    {
        if (grid.y > 36 && grid.y <= 37)
        {
            y = -1;
        }
    }


    int timeDelta{ 120 };
    sf::Time animateMovement = movementClock.getElapsedTime();
    int time{ animateMovement.asMilliseconds() };
    if (time >= timeDelta)
    {
        if (y < 0)
        {
            switch (animCode)
            {
            case 0:
                textureUpdate(animFlag.upABool);
                animCode += 1;
                break;
            case 1:
                textureUpdate(animFlag.upBBool);
                animCode += 1;
                break;
            case 2:
                textureUpdate(animFlag.upABool);
                animCode += 1;
                break;
            case 3:
                textureUpdate(animFlag.upCBool);
                animCode = 0;
                break;
            default:
                break;
            }

        }
        else if (y > 0)
        {
            switch (animCode)
            {
            case 0:
                textureUpdate(animFlag.downABool);
                animCode += 1;
                break;
            case 1:
                textureUpdate(animFlag.downBBool);
                animCode += 1;
                break;
            case 2:
                textureUpdate(animFlag.downABool);
                animCode += 1;
                break;
            case 3:
                textureUpdate(animFlag.downCBool);
                animCode = 0;
                break;
            default:
                break;
            }

        }
        else if (x < 0)
        {
            switch (animCode)
            {
            case 0:
                textureUpdate(animFlag.leftABool);
                animCode += 1;
                break;
            case 1:
                textureUpdate(animFlag.leftBBool);
                animCode += 1;
                break;
            case 2:
                textureUpdate(animFlag.leftABool);
                animCode += 1;
                break;
            case 3:
                textureUpdate(animFlag.leftCBool);
                animCode = 0;
                break;
            default:
                break;
            }

        }
        else if (x > 0)
        {
            switch (animCode)
            {
            case 0:
                textureUpdate(animFlag.rightABool);
                animCode += 1;
                break;
            case 1:
                textureUpdate(animFlag.rightBBool);
                animCode += 1;
                break;
            case 2:
                textureUpdate(animFlag.rightABool);
                animCode += 1;
                break;
            case 3:
                textureUpdate(animFlag.rightCBool);
                animCode = 0;
                break;
            default:
                break;
            }

        }
        movementClock.restart();
    }
}
void CharacterSprite::checkTimeout()
{
    int timeDelta{ 1250 };
    sf::Time animateMovement = movementClock.getElapsedTime();
    int time{ animateMovement.asMilliseconds() };
    if (time >= timeDelta)
    {

        if (animFlag.upABool || animFlag.upBBool || animFlag.upCBool)
        {
            textureUpdate(animFlag.upABool);
            animCode = 0;
        }
        else if (animFlag.leftABool || animFlag.leftBBool || animFlag.leftCBool)
        {
            textureUpdate(animFlag.idleLBool);
            animCode = 0;
        }
        else if (animFlag.rightABool || animFlag.rightBBool || animFlag.rightCBool)
        {
            textureUpdate(animFlag.idleRBool);
            animCode = 0;
        }
        else if (animFlag.downABool || animFlag.downBBool || animFlag.downCBool)
        {
            textureUpdate(animFlag.downABool);
            animCode = 0;
        }

        //textureUpdate();

    }
}
// Private
void CharacterSprite::m_clearBools()
{
    animFlag.downABool = false;
    animFlag.downBBool = false;
    animFlag.downCBool = false;
    animFlag.upABool = false;
    animFlag.upBBool = false;
    animFlag.upCBool = false;
    animFlag.leftABool = false;
    animFlag.leftBBool = false;
    animFlag.leftCBool = false;
    animFlag.rightABool = false;
    animFlag.rightBBool = false;
    animFlag.rightCBool = false;
    animFlag.frontBool = false;
    animFlag.backBool = false;
    animFlag.idleRBool = false;
    animFlag.idleLBool = false;
    animFlag.shrug1RBool = false;
    animFlag.shrug1LBool = false;
    animFlag.shrug2RBool = false;
    animFlag.shrug2LBool = false;
    animFlag.shrug2mouthRBool = false;
    animFlag.shrug2mouthLBool = false;
    animFlag.crawlRBool = false;
    animFlag.crawlLBool = false;
    animFlag.pointRBool = false;
    animFlag.pointLBool = false;
    animFlag.handsUpRBool = false;
    animFlag.handsUpLBool = false;
    animFlag.pushRBool = false;
    animFlag.pushLBool = false;
    animFlag.deadRBool = false;
    animFlag.deadLBool = false;
    animFlag.hitRBool = false;
    animFlag.hitLBool = false;
}

// Character
// Public
Character::Character(int id) : m_id(id), characterSprite(id)
{
    order = id;
    movementStepSize = 4;

    coordVector.push_back(0);
    coordVector.push_back(0);
}
void Character::follow(Character& leadingCharacter, int pixelSize)
{
    int x{ leadingCharacter.coordVector.front() };
    int y{ leadingCharacter.coordVector[1] };

    if (intify(leadingCharacter.coordVector.size()) > 64 / leadingCharacter.movementStepSize)
    {
        characterSprite.shaderSprite.sprite.move(pairF(x * movementStepSize * pixelSize, y * movementStepSize * pixelSize));

        leadingCharacter.coordVector.erase(leadingCharacter.coordVector.begin());
        leadingCharacter.coordVector.erase(leadingCharacter.coordVector.begin());

        coordVector.push_back(x);
        coordVector.push_back(y);
        
        characterSprite.changeAnimationState(x, y, pixelSize);
    }
}
void Character::swapOrder(Character& otherCharacter)
{
    std::swap(order, otherCharacter.order);
}