#pragma once
#include <SFML/Graphics.hpp>
#include "../ImageResources/arsonImages.h"
#include "../ImageResources/coleImages.h"
#include "../ImageResources/gaiaImages.h"
#include "../ImageResources/nekoImages.h"
#include "constExpressions.h"

enum CharacterID
{
    ArsonID,
    GaiaID,
    ColeID,
    NekoID
};
enum SpriteColor
{
    Default,
    Inverted,
    Black,
    Transparent,
    Blue,
    Dark
};

class Character
{
private:
    int m_id;
public:
    sf::Sprite sprite;
    sf::Texture spriteTexture;
    sf::Clock movementClock;
    std::vector<uint8_t> currentTexture;
    int spriteW;
    int spriteH;
    int spriteColour;
    int order;
    int animCode;

    Character(int id);
    void textureUpdate();
    void clearBools();
    void pickArray();
    void changeAnimationState(int x, int y);
    void swapOrder(Character& otherCharacter);
    void follow(Character& otherCharacter, int movementStepSize);
    void checkTimeout();
    std::vector<int> coordVector;

    // Animation State Booleans
    bool downABool{ true }; // Default
    bool downBBool{ false };
    bool downCBool{ false };
    bool upABool{ false };
    bool upBBool{ false };
    bool upCBool{ false };
    bool leftABool{ false };
    bool leftBBool{ false };
    bool leftCBool{ false };
    bool rightABool{ false };
    bool rightBBool{ false };
    bool rightCBool{ false };
    bool frontBool{ false };
    bool backBool{ false };
    bool idleRBool{ false };
    bool idleLBool{ false };
    bool shrug1RBool{ false };
    bool shrug1LBool{ false };
    bool shrug2RBool{ false };
    bool shrug2LBool{ false };
    bool shrug2mouthRBool{ false };
    bool shrug2mouthLBool{ false };
    bool crawlRBool{ false };
    bool crawlLBool{ false };
    bool pointRBool{ false };
    bool pointLBool{ false };
    bool handsUpRBool{ false };
    bool handsUpLBool{ false };
    bool pushRBool{ false };
    bool pushLBool{ false };
    bool deadRBool{ false };
    bool deadLBool{ false };
    bool hitRBool{ false };
    bool hitLBool{ false };
};