#pragma once
#include "character.h"

Character::Character(int id) : m_id(id) 
{
    spriteW = 32;
    spriteH = 32;
    spriteColour = Default;
    order = id;
    textureUpdate();
    sprite.setScale(pairF(2, 2));
    coordVector.push_back(0);
    coordVector.push_back(0);
}

void Character::textureUpdate()
{
    //std::cout << animCode << " ";
    spriteTexture.create(spriteW, spriteH);
    sf::Uint8* pixels = new sf::Uint8[spriteW * spriteH * 4];

    uint8_t rw{ 255 };
    uint8_t gw{ 0 };
    uint8_t bw{ 0 };
    uint8_t aw{ 255 };

    pickArray();

    for (int i = 0; i < spriteW * spriteH * 4; i += 4)
    {
        //every iteration will call in order every pixel until done.
        rw = currentTexture[0 + i];
        gw = currentTexture[1 + i];
        bw = currentTexture[2 + i];
        aw = currentTexture[3 + i];

        // Sprite colorizer - not implemented yet

        switch (spriteColour)
        {
        case Default:
            pixels[i + 0] = rw;
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Inverted:
            if (rw <= 34 && gw <= 34 && bw <= 34)
            {
                pixels[i + 0] = rw; // assigns the value at r to the pixels object
                pixels[i + 1] = gw;
                pixels[i + 2] = bw;
            }
            else
            {
                pixels[i + 0] = 255 - rw; // assigns the value at r to the pixels object
                pixels[i + 1] = 255 - gw;
                pixels[i + 2] = 255 - bw;
            }
            pixels[i + 3] = aw;
            break;
        case Black:
            if (rw > 45 || gw > 45 || bw > 45)
            {
                aw = 0;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Transparent:
            if (aw > 250)
            {
                aw = 127;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Blue:
            if (rw + gw + bw > 255)
            {
                bw = 255;
            }
            else
            {
                bw = rw + gw + bw;
                rw = 0;
                gw = 0;
            }
            pixels[i + 0] = rw; // assigns the value at r to the pixels object
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        case Dark:
            pixels[i + 0] = rw / 2; // assigns the value at r to the pixels object
            pixels[i + 1] = gw / 2;
            pixels[i + 2] = bw / 2;
            pixels[i + 3] = aw;
            break;
        default:
            pixels[i + 0] = rw;
            pixels[i + 1] = gw;
            pixels[i + 2] = bw;
            pixels[i + 3] = aw;
            break;
        }


    }
    spriteTexture.update(pixels);
    sprite.setTexture(spriteTexture);
    delete[] pixels;
    currentTexture.clear();
    //movementClock.restart();
}

void Character::clearBools()
{
    downABool = false;
    downBBool = false;
    downCBool = false;
    upABool = false;
    upBBool = false;
    upCBool = false;
    leftABool = false;
    leftBBool = false;
    leftCBool = false;
    rightABool = false;
    rightBBool = false;
    rightCBool = false;
    frontBool = false;
    backBool = false;
    idleRBool = false;
    idleLBool = false;
    shrug1RBool = false;
    shrug1LBool = false;
    shrug2RBool = false;
    shrug2LBool = false;
    shrug2mouthRBool = false;
    shrug2mouthLBool = false;
    crawlRBool = false;
    crawlLBool = false;
    pointRBool = false;
    pointLBool = false;
    handsUpRBool = false;
    handsUpLBool = false;
    pushRBool = false;
    pushLBool = false;
    deadRBool = false;
    deadLBool = false;
    hitRBool = false;
    hitLBool = false;
}

void Character::pickArray()
{
    //currentTexture.clear(); //Just in case?
    switch (m_id)
    {
    case 0:
        break;
    case 1:
        for (int i = 0; i < arsonDownA.size(); i++)
        { // Arson
            if (downABool) { currentTexture.push_back(arsonDownA[i]); }
            else if (downBBool) { currentTexture.push_back(arsonDownB[i]); }
            else if (downCBool) { currentTexture.push_back(arsonDownC[i]); }
            else if (upABool) { currentTexture.push_back(arsonUpA[i]); }
            else if (upBBool) { currentTexture.push_back(arsonUpB[i]); }
            else if (upCBool) { currentTexture.push_back(arsonUpC[i]); }
            else if (leftABool) { currentTexture.push_back(arsonLeftA[i]); }
            else if (leftBBool) { currentTexture.push_back(arsonLeftB[i]); }
            else if (leftCBool) { currentTexture.push_back(arsonLeftC[i]); }
            else if (rightABool) { currentTexture.push_back(arsonRightA[i]); }
            else if (rightBBool) { currentTexture.push_back(arsonRightB[i]); }
            else if (rightCBool) { currentTexture.push_back(arsonRightC[i]); }
            else if (frontBool) { currentTexture.push_back(arsonFront[i]); }
            else if (backBool) { currentTexture.push_back(arsonBack[i]); }
            else if (idleLBool) { currentTexture.push_back(arsonIdleL[i]); }
            else if (idleRBool) { currentTexture.push_back(arsonIdleR[i]); }
            else if (shrug1RBool) { currentTexture.push_back(arsonShrug1R[i]); }
            else if (shrug1LBool) { currentTexture.push_back(arsonShrug1L[i]); }
            else if (shrug2RBool) { currentTexture.push_back(arsonShrug2R[i]); }
            else if (shrug2LBool) { currentTexture.push_back(arsonShrug2L[i]); }
            else if (shrug2mouthRBool) { currentTexture.push_back(arsonShrug2mouthR[i]); }
            else if (shrug2mouthLBool) { currentTexture.push_back(arsonShrug2mouthL[i]); }
            else if (crawlRBool) { currentTexture.push_back(arsonCrawlR[i]); }
            else if (crawlLBool) { currentTexture.push_back(arsonCrawlL[i]); }
            else if (pointRBool) { currentTexture.push_back(arsonPointR[i]); }
            else if (pointLBool) { currentTexture.push_back(arsonPointL[i]); }
            else if (handsUpRBool) { currentTexture.push_back(arsonHandsUpR[i]); }
            else if (handsUpLBool) { currentTexture.push_back(arsonHandsUpL[i]); }
            else if (pushRBool) { currentTexture.push_back(arsonPushR[i]); }
            else if (pushLBool) { currentTexture.push_back(arsonPushL[i]); }
            else if (deadRBool) { currentTexture.push_back(arsonDeadR[i]); }
            else if (deadLBool) { currentTexture.push_back(arsonDeadL[i]); }
            else if (hitRBool) { currentTexture.push_back(arsonHitR[i]); }
            else if (hitLBool) { currentTexture.push_back(arsonHitL[i]); }
        }
        break;
    case 2:
        for (int i = 0; i < arsonDownA.size(); i++)
        { // Arson
            if (downABool) { currentTexture.push_back(arsonDownA[i]); }
            else if (downBBool) { currentTexture.push_back(arsonDownB[i]); }
            else if (downCBool) { currentTexture.push_back(arsonDownC[i]); }
            else if (upABool) { currentTexture.push_back(arsonUpA[i]); }
            else if (upBBool) { currentTexture.push_back(arsonUpB[i]); }
            else if (upCBool) { currentTexture.push_back(arsonUpC[i]); }
            else if (leftABool) { currentTexture.push_back(arsonLeftA[i]); }
            else if (leftBBool) { currentTexture.push_back(arsonLeftB[i]); }
            else if (leftCBool) { currentTexture.push_back(arsonLeftC[i]); }
            else if (rightABool) { currentTexture.push_back(arsonRightA[i]); }
            else if (rightBBool) { currentTexture.push_back(arsonRightB[i]); }
            else if (rightCBool) { currentTexture.push_back(arsonRightC[i]); }
            else if (frontBool) { currentTexture.push_back(arsonFront[i]); }
            else if (backBool) { currentTexture.push_back(arsonBack[i]); }
            else if (idleLBool) { currentTexture.push_back(arsonIdleL[i]); }
            else if (idleRBool) { currentTexture.push_back(arsonIdleR[i]); }
            else if (shrug1RBool) { currentTexture.push_back(arsonShrug1R[i]); }
            else if (shrug1LBool) { currentTexture.push_back(arsonShrug1L[i]); }
            else if (shrug2RBool) { currentTexture.push_back(arsonShrug2R[i]); }
            else if (shrug2LBool) { currentTexture.push_back(arsonShrug2L[i]); }
            else if (shrug2mouthRBool) { currentTexture.push_back(arsonShrug2mouthR[i]); }
            else if (shrug2mouthLBool) { currentTexture.push_back(arsonShrug2mouthL[i]); }
            else if (crawlRBool) { currentTexture.push_back(arsonCrawlR[i]); }
            else if (crawlLBool) { currentTexture.push_back(arsonCrawlL[i]); }
            else if (pointRBool) { currentTexture.push_back(arsonPointR[i]); }
            else if (pointLBool) { currentTexture.push_back(arsonPointL[i]); }
            else if (handsUpRBool) { currentTexture.push_back(arsonHandsUpR[i]); }
            else if (handsUpLBool) { currentTexture.push_back(arsonHandsUpL[i]); }
            else if (pushRBool) { currentTexture.push_back(arsonPushR[i]); }
            else if (pushLBool) { currentTexture.push_back(arsonPushL[i]); }
            else if (deadRBool) { currentTexture.push_back(arsonDeadR[i]); }
            else if (deadLBool) { currentTexture.push_back(arsonDeadL[i]); }
            else if (hitRBool) { currentTexture.push_back(arsonHitR[i]); }
            else if (hitLBool) { currentTexture.push_back(arsonHitL[i]); }
        }
        break;
    case 3:
        for (int i = 0; i < arsonDownA.size(); i++)
        { // Arson
            if (downABool) { currentTexture.push_back(arsonDownA[i]); }
            else if (downBBool) { currentTexture.push_back(arsonDownB[i]); }
            else if (downCBool) { currentTexture.push_back(arsonDownC[i]); }
            else if (upABool) { currentTexture.push_back(arsonUpA[i]); }
            else if (upBBool) { currentTexture.push_back(arsonUpB[i]); }
            else if (upCBool) { currentTexture.push_back(arsonUpC[i]); }
            else if (leftABool) { currentTexture.push_back(arsonLeftA[i]); }
            else if (leftBBool) { currentTexture.push_back(arsonLeftB[i]); }
            else if (leftCBool) { currentTexture.push_back(arsonLeftC[i]); }
            else if (rightABool) { currentTexture.push_back(arsonRightA[i]); }
            else if (rightBBool) { currentTexture.push_back(arsonRightB[i]); }
            else if (rightCBool) { currentTexture.push_back(arsonRightC[i]); }
            else if (frontBool) { currentTexture.push_back(arsonFront[i]); }
            else if (backBool) { currentTexture.push_back(arsonBack[i]); }
            else if (idleLBool) { currentTexture.push_back(arsonIdleL[i]); }
            else if (idleRBool) { currentTexture.push_back(arsonIdleR[i]); }
            else if (shrug1RBool) { currentTexture.push_back(arsonShrug1R[i]); }
            else if (shrug1LBool) { currentTexture.push_back(arsonShrug1L[i]); }
            else if (shrug2RBool) { currentTexture.push_back(arsonShrug2R[i]); }
            else if (shrug2LBool) { currentTexture.push_back(arsonShrug2L[i]); }
            else if (shrug2mouthRBool) { currentTexture.push_back(arsonShrug2mouthR[i]); }
            else if (shrug2mouthLBool) { currentTexture.push_back(arsonShrug2mouthL[i]); }
            else if (crawlRBool) { currentTexture.push_back(arsonCrawlR[i]); }
            else if (crawlLBool) { currentTexture.push_back(arsonCrawlL[i]); }
            else if (pointRBool) { currentTexture.push_back(arsonPointR[i]); }
            else if (pointLBool) { currentTexture.push_back(arsonPointL[i]); }
            else if (handsUpRBool) { currentTexture.push_back(arsonHandsUpR[i]); }
            else if (handsUpLBool) { currentTexture.push_back(arsonHandsUpL[i]); }
            else if (pushRBool) { currentTexture.push_back(arsonPushR[i]); }
            else if (pushLBool) { currentTexture.push_back(arsonPushL[i]); }
            else if (deadRBool) { currentTexture.push_back(arsonDeadR[i]); }
            else if (deadLBool) { currentTexture.push_back(arsonDeadL[i]); }
            else if (hitRBool) { currentTexture.push_back(arsonHitR[i]); }
            else if (hitLBool) { currentTexture.push_back(arsonHitL[i]); }
        }
        break;
    case 4:
        for (int i = 0; i < arsonDownA.size(); i++)
        { // Arson
            if (downABool) { currentTexture.push_back(arsonDownA[i]); }
            else if (downBBool) { currentTexture.push_back(arsonDownB[i]); }
            else if (downCBool) { currentTexture.push_back(arsonDownC[i]); }
            else if (upABool) { currentTexture.push_back(arsonUpA[i]); }
            else if (upBBool) { currentTexture.push_back(arsonUpB[i]); }
            else if (upCBool) { currentTexture.push_back(arsonUpC[i]); }
            else if (leftABool) { currentTexture.push_back(arsonLeftA[i]); }
            else if (leftBBool) { currentTexture.push_back(arsonLeftB[i]); }
            else if (leftCBool) { currentTexture.push_back(arsonLeftC[i]); }
            else if (rightABool) { currentTexture.push_back(arsonRightA[i]); }
            else if (rightBBool) { currentTexture.push_back(arsonRightB[i]); }
            else if (rightCBool) { currentTexture.push_back(arsonRightC[i]); }
            else if (frontBool) { currentTexture.push_back(arsonFront[i]); }
            else if (backBool) { currentTexture.push_back(arsonBack[i]); }
            else if (idleLBool) { currentTexture.push_back(arsonIdleL[i]); }
            else if (idleRBool) { currentTexture.push_back(arsonIdleR[i]); }
            else if (shrug1RBool) { currentTexture.push_back(arsonShrug1R[i]); }
            else if (shrug1LBool) { currentTexture.push_back(arsonShrug1L[i]); }
            else if (shrug2RBool) { currentTexture.push_back(arsonShrug2R[i]); }
            else if (shrug2LBool) { currentTexture.push_back(arsonShrug2L[i]); }
            else if (shrug2mouthRBool) { currentTexture.push_back(arsonShrug2mouthR[i]); }
            else if (shrug2mouthLBool) { currentTexture.push_back(arsonShrug2mouthL[i]); }
            else if (crawlRBool) { currentTexture.push_back(arsonCrawlR[i]); }
            else if (crawlLBool) { currentTexture.push_back(arsonCrawlL[i]); }
            else if (pointRBool) { currentTexture.push_back(arsonPointR[i]); }
            else if (pointLBool) { currentTexture.push_back(arsonPointL[i]); }
            else if (handsUpRBool) { currentTexture.push_back(arsonHandsUpR[i]); }
            else if (handsUpLBool) { currentTexture.push_back(arsonHandsUpL[i]); }
            else if (pushRBool) { currentTexture.push_back(arsonPushR[i]); }
            else if (pushLBool) { currentTexture.push_back(arsonPushL[i]); }
            else if (deadRBool) { currentTexture.push_back(arsonDeadR[i]); }
            else if (deadLBool) { currentTexture.push_back(arsonDeadL[i]); }
            else if (hitRBool) { currentTexture.push_back(arsonHitR[i]); }
            else if (hitLBool) { currentTexture.push_back(arsonHitL[i]); }
        }
        break;
    default:
        break;
    }
}

void Character::changeAnimationState(int x, int y)
{
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
                clearBools();
                upABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 1:
                clearBools();
                upBBool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 2:
                clearBools();
                upABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 3:
                clearBools();
                upCBool = true;
                textureUpdate();
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
                clearBools();
                downABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 1:
                clearBools();
                downBBool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 2:
                clearBools();
                downABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 3:
                clearBools();
                downCBool = true;
                textureUpdate();
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
                clearBools();
                leftABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 1:
                clearBools();
                leftBBool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 2:
                clearBools();
                leftABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 3:
                clearBools();
                leftCBool = true;
                textureUpdate();
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
                clearBools();
                rightABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 1:
                clearBools();
                rightBBool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 2:
                clearBools();
                rightABool = true;
                textureUpdate();
                animCode += 1;
                break;
            case 3:
                clearBools();
                rightCBool = true;
                textureUpdate();
                animCode = 0;
                break;
            default:
                break;
            }

        }
        movementClock.restart();

    }


    
}

void Character::swapOrder(Character& otherCharacter)
{
    std::swap(order, otherCharacter.order);
}

void Character::follow(Character& otherCharacter, int movementStepSize)
{
    int x{ otherCharacter.coordVector.front() };
    int y{ otherCharacter.coordVector[1] };
    if (otherCharacter.coordVector.size() == 16)
    {
        sprite.move(x * movementStepSize, y * movementStepSize);
        
        otherCharacter.coordVector.erase(otherCharacter.coordVector.begin());
        otherCharacter.coordVector.erase(otherCharacter.coordVector.begin());

        coordVector.push_back(x);
        coordVector.push_back(y);
        
        changeAnimationState(x, y);
    }
}

void Character::checkTimeout()
{
    int timeDelta{ 2000 };
    sf::Time animateMovement = movementClock.getElapsedTime();
    int time{ animateMovement.asMilliseconds() };
    if (time >= timeDelta)
    {

        if (upABool || upBBool || upCBool)
        {
            clearBools();
            backBool = true;
            textureUpdate();
            animCode = 0;
        }
        else if (leftABool || leftBBool || leftCBool)
        {
            clearBools();
            idleLBool = true;
            textureUpdate();
            animCode = 0;
        }
        else if (rightABool || rightBBool || rightCBool)
        {
            clearBools();
            idleRBool = true;
            textureUpdate();
            animCode = 0;
        }
        else if (downABool || downBBool || downCBool)
        {
            clearBools();
            frontBool = true;
            textureUpdate();
            animCode = 0;
        }

        textureUpdate();
        
    }
}