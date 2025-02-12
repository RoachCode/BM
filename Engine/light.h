#pragma once
#include <SFML/Graphics.hpp>
#include "constExpressions.h"
#include "view.h"

class Light : public sf::Drawable, public View
{
private:
	const char m_vertexShader[151] =
		"void main()"
		"{"
			"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
			"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
			"gl_FrontColor = gl_Color;"
		"}";
	//TODO: clamp colors for a more pixelly feel.
	const char m_radialGradient[376] =
		"uniform vec4 color;"
		"uniform vec2 center;"
		"uniform float radius;"
		"uniform float expand;"
		"uniform float windowHeight;"
		"void main(void)"
		"{"
			"vec2 centerFromSfml = vec2(center.x, windowHeight - center.y);"
			"vec2 p = (gl_FragCoord.xy - centerFromSfml) / radius;"
			"float r = sqrt(dot(p, p));"
			"if (r < 1.0)"
			"{"
				"gl_FragColor = mix(color, gl_Color, (r - expand) / (1 - expand));"
			"}"
			"else"
			"{"
				"gl_FragColor = gl_Color;"
			"}"
		"}";
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		//states.transform *= getTransform();
		states.shader = &shader;
		target.draw(circle, states);
	}

public:

	sf::CircleShape circle;
	sf::Shader shader;

	Light()
	{
		//position = pos;

		circle.setRadius(100.f);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		//circle.setPosition(this->getPosition());
		circle.setFillColor(sf::Color::Transparent);

		shader.loadFromMemory(m_vertexShader, m_radialGradient);
		shader.setUniform("windowHeight", floatify(View::getScreenSize().y));
		shader.setUniform("color", sf::Glsl::Vec4(1.f, 1.f, 0.85f, 1.f)); // Blue color hex, normalized
		shader.setUniform("center", circle.getPosition());
		shader.setUniform("radius", circle.getRadius());
		shader.setUniform("expand", 0.f);
	}

	void setPosition(sf::Vector2f pos, sf::Vector2f worldPos)
	{
		circle.setPosition(pos);
		shader.setUniform("center", worldPos);
	}
	//template <typename T>
	//void setPosition(T const& x, T const& y, sf::RenderWindow &window) { setPosition(pairF(x, y), window); }
};