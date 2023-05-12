#pragma once
#include <SFML/Graphics.hpp>
#include "particles.h"

class Flow
{
public:
	unsigned int width;
	unsigned int height;
	sf::VertexArray m_vertices;
	sf::Image image;
	sf::Texture gradient;
	sf::Vector2u tileSize;
	sf::RectangleShape line;
	std::vector<float> angleVector;
	sf::CircleShape tracer;

	Flow()
	{
		width = sf::VideoMode::getDesktopMode().width / 2;
		height = sf::VideoMode::getDesktopMode().height / 2;
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);
		tileSize = sf::Vector2u(width / 50, height / 50);
		line.setSize(sf::Vector2f(height / 50 / 2, 0.5));

		tracer.setRadius(2.f);
		tracer.setFillColor(sf::Color::Cyan);
		tracer.setPosition(400, 21);

		sf::Uint8* pixels = new sf::Uint8[400];
		for (int i = 0; i < 100; i++)
		{
			pixels[i * 4 + 0] = 255;
			pixels[i * 4 + 1] = 255 - (i * 2);
			pixels[i * 4 + 2] = 255 - (i * 2);
			pixels[i * 4 + 3] = 255;
		}

		image.create(100, 1, pixels);
		gradient.loadFromImage(image);
		line.setTexture(&gradient);
		delete[] pixels;

		for (unsigned int i = 0; i < width / tileSize.x; i++)
		{
			for (unsigned int j = 0; j < height / tileSize.y; j++)
			{

				float angle = j * PI;
				angleVector.push_back(angle);
			}
		}
	}



};