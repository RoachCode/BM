#pragma once
#include "character.h"
#include "view.h"

// CharacterSprite
// Public
CharacterSprite::CharacterSprite(int id) : m_id(id)
{
    // Define sprite size
    width = TILE_SIZE;
    height = TILE_SIZE;

    // Build Texture Atlas and set to Sprite
    buildTextureAtlas();
    shaderSprite.sprite.setTexture(textureAtlas);

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

    // Set sprite texture rect (with animation flag boolean)
    m_clearAnimationFlags();
    textureUpdate(animFlag.downABool);

}
void CharacterSprite::buildTextureAtlas()
{
    //Currnet list of textures available: (bracketed means it is copied from another array)
    //UpA, UpB, UpC, DownA, DownB, DownC, LeftA, (RightA), LeftB, (RightB), LeftC, (RightC), IdleL, (IdleR), back, front
    int textureArrayCount{ 12 };
    sf::Image bigImage;
    // +4 is for the ones above in brackets.
    bigImage.create(TILE_SIZE * (textureArrayCount + 4), TILE_SIZE, sf::Color::Transparent);
    std::vector<std::vector<uint8_t>*> imageVectorsPtr;
    // populate imageVectorsPtr with correct data (by character id)
    switch (m_id)
    {
    case ArsonID:
        imageVectorsPtr = 
        {
            &arsonUpA, &arsonUpB, &arsonUpC, &arsonDownA, &arsonDownB, &arsonDownC, 
            &arsonLeftA, &arsonLeftB, &arsonLeftC, &arsonIdleL, &arsonBack, &arsonFront,
        };
        break;
    case GaiaID:
        imageVectorsPtr =
        {
            &gaiaUpA, &gaiaUpB, &gaiaUpC, &gaiaDownA, &gaiaDownB, &gaiaDownC,
            &gaiaLeftA, &gaiaLeftB, &gaiaLeftC, &gaiaIdleL, &gaiaBack, &gaiaFront,
        };
        break;
    case ColeID:
        imageVectorsPtr =
        {
            &coleUpA, &coleUpB, &coleUpC, &coleDownA, &coleDownB, &coleDownC,
            &coleLeftA, &coleLeftB, &coleLeftC, &coleIdleL, &coleBack, &coleFront,
        };
        break;
    case NekoID:
        imageVectorsPtr =
        {
            &nekoUpA, &nekoUpB, &nekoUpC, &nekoDownA, &nekoDownB, &nekoDownC,
            &nekoLeftA, &nekoLeftB, &nekoLeftC, &nekoIdleL, &nekoBack, &nekoFront,
        };
        break;
    default:
        return;
    }

    // when copying a texture from another
    int copierOffset{ 0 };

    for (unsigned int i = 0; i < textureArrayCount; i++)
    {
        sf::Image image;
        image.create(TILE_SIZE, TILE_SIZE, imageVectorsPtr[i]->data());
        bigImage.copy(image, (i + copierOffset) * TILE_SIZE, 0);

        // LeftA, LeftB, LeftC, IdleL
        if (i == 6 || i == 7 || i == 8 || i == 9)
        { image.flipHorizontally(); copierOffset += 1; bigImage.copy(image, (i + copierOffset) * TILE_SIZE, 0); }
    }
    imageVectorsPtr.clear();
    textureAtlas.create(TILE_SIZE * (textureArrayCount + copierOffset), TILE_SIZE);
    textureAtlas.loadFromImage(bigImage);
}
void CharacterSprite::textureUpdate()
{
    const int positionOffset{ m_getAnimationFlagIndex() };
    shaderSprite.sprite.setTextureRect(sf::IntRect(positionOffset * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
}
void CharacterSprite::textureUpdate(bool& inputBool)
{
    m_setAnimationFlag(inputBool);
    textureUpdate();
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
    }
}

// Private
void CharacterSprite::m_clearAnimationFlags()
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
void CharacterSprite::m_setAnimationFlag(bool& inputBool)
{
    m_clearAnimationFlags();
    inputBool = true;
}
const int CharacterSprite::m_getAnimationFlagIndex() const
{
    //UpA, UpB, UpC, DownA, DownB, DownC, LeftA, (RightA), LeftB, (RightB), LeftC, (RightC), IdleL, (IdleR), back, front
    if (animFlag.upABool) { return 0; }
    else if (animFlag.upBBool) { return 1; }
    else if (animFlag.upCBool) { return 2; }
    else if (animFlag.downABool) { return 3; }
    else if (animFlag.downBBool) { return 4; }
    else if (animFlag.downCBool) { return 5; }
    else if (animFlag.leftABool) { return 6; }
    else if (animFlag.rightABool) { return 7; }
    else if (animFlag.leftBBool) { return 8; }
    else if (animFlag.rightBBool) { return 9; }
    else if (animFlag.leftCBool) { return 10; }
    else if (animFlag.rightCBool) { return 11; }
    else if (animFlag.idleLBool) { return 12; }
    else if (animFlag.idleRBool) { return 13; }
    else if (animFlag.backBool) { return 14; }
    else if (animFlag.frontBool) { return 15; }
    else { return 3; } //Default
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