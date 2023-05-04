#pragma once
#include <SFML/Graphics.hpp>

class Sprite 
{
public:
    //sf::Sprite sprite;
    //sf::Texture spriteTexture;
    sf::CircleShape shape;
    std::vector<sf::CircleShape> shapeVector;
    
    Sprite()
    {
        shape.setRadius(100.f);
        shape.setFillColor(sf::Color(0, 0, 255, 125));
        shapeVector.push_back(shape);
    }
    /*
    void textureUpdate()
    {
        spriteTexture.create(32, 32);
        sf::Uint8* pixels = new sf::Uint8[spriteW * spriteH * 4];

        uint8_t rw{ 255 };
        uint8_t gw{ 0 };
        uint8_t bw{ 0 };
        uint8_t aw{ 255 };

        for (int i = 0; i < spriteW * spriteH * 4; i += 4)
        {
            //every iteration will call in order every pixel until done.
            rw = temp[0 + i];
            gw = temp[1 + i];
            bw = temp[2 + i];
            aw = temp[3 + i];

            // Sprite colorizer - not implemented yet
            /*
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
                if (rw > 25 || gw > 25 || bw > 25)
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
    }
*/
private:
};