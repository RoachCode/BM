#pragma once
#include <SFML/Graphics.hpp>
#include "../ImageResources/arsonImages.h"
#include "../ImageResources/coleImages.h"
#include "../ImageResources/gaiaImages.h"
#include "../ImageResources/nekoImages.h"
#include "constExpressions.h"

const char colorFrag[170] =
"uniform sampler2D texture;"
"uniform vec4 colorIn = vec4(1.0, 1.0, 1.0, 1.0);"
"void main()"
"{"
    "vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);"
    "gl_FragColor = pixel * colorIn;"
"}";

const char outlineFrag[335] =
"uniform sampler2D texture;"
"uniform float blackThreshhold = 0.2;"
"void main()"
"{"
    "vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);"
    "float grey = (pixel.r + pixel.g + pixel.b + 0.01) / 3.0;"
    "if (grey < blackThreshhold && pixel.a > 0.5)"
        "gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);"
    "else "
        "gl_FragColor = vec4(0.0, 0.0, 0.0, (1.0 - grey) / 2 * pixel.a);"
"}";

const char invertFrag[315] =
"uniform sampler2D texture;"
"uniform float blackThreshhold = 0.2;"
"void main()"
"{"
    "vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);"
    "if (pixel.r < blackThreshhold && pixel.g < blackThreshhold && pixel.b < blackThreshhold)"
        "gl_FragColor = pixel;"
    "else "
        "gl_FragColor = vec4(1.0 - pixel.r, 1.0 - pixel.g, 1.0 - pixel.b, pixel.a);"
"}";

struct ShaderSprite
{
    sf::Sprite sprite;
    sf::RenderStates renderStates;
};
struct AnimFlag
{
    // Animation State Booleans
    bool downABool{ false };
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

class CharacterSprite
{
private:
    int m_id;
    void m_clearBools();

public:
    int width{ 0 };
    int height{ 0 };
    int animCode{ 0 };
    ShaderSprite shaderSprite;
    AnimFlag animFlag;
    sf::Shader colorShader;
    sf::Shader outlineShader;
    sf::Shader invertShader;
    sf::Texture texture;
    sf::Texture textureAtlas;
    SpriteColor spriteColor;
    sf::Clock movementClock;
    std::vector<uint8_t> currentTextureVector;

    CharacterSprite(int id);

    void textureUpdate();
    void textureUpdate(bool& inputBool);
    void pickArray();
    void changeAnimationState(int x, int y, int pixelSize);
    void checkTimeout();
    void setSpriteShader(SpriteColor colorEnum = SpriteColor::Default);
    void buildTextureAtlas();
};

class Character
{
private:
    int m_id;

public:
    int order;
    int movementStepSize;
    std::vector<int> coordVector;
    CharacterSprite characterSprite;

    Character(int id);
    void swapOrder(Character& otherCharacter);
    void follow(Character& otherCharacter, int movementStepSize);
};