#pragma once
#pragma warning( disable : 4244 ) // Line 111. I want to perform a narrowing conversion.
#include "OpenSimplexNoise.h"
#include "constExpressions.h"


class Noise
{
public:
	Noise()
	{
		startOctave = 8;
		m_simplexOctaves = 4;
		m_simplexSizeX = 0;
		m_simplexSizeY = 0;
		m_simplexSizeX = 0;
		m_simplexSizeY = 0;
		simplexSpeed = 0;
		simplexStepper = 0;
	}
	// Data
	// Vector array of angles, one per cell
	std::vector<float> angleVector;
	std::vector<float> m_xyValues;
	std::vector<int> m_tempContainer;
	std::deque<sf::Uint8> m_simplexData;

	float m_simplexSizeX;
	float m_simplexSizeY;
	int m_simplexOctaves;
	int startOctave;

	// For fullscreen cloud noise
	int simplexSpeed;
	int simplexStepper;

	sf::RectangleShape noise;
	sf::Texture noiseTexture;
	// For animated noise
	float qdMod{ 0.f };
	bool isWater{ false };
	bool reverse{ false };
	int animationDepth{};
	float stepSize{};

	void m_createSimplexValues(int x, int y)
	{
		m_xyValues.clear();
		int octave{ startOctave }; // needs to be 1 for water
		float x1 = 0;
		float x2 = 1;
		float y1 = 0;
		float y2 = 1;
		for (int k = 0; k < m_simplexOctaves; k++)
		{
			octave *= 2;
			for (int iy = 0; iy < y; ++iy)
			{
				for (int ix = 0; ix < x; ++ix)
				{
					// these offsets define the circles
					float s = static_cast<float>(ix) / static_cast<float>(x);
					float t = static_cast<float>(iy) / static_cast<float>(y);

					// clamping to [0, 1]
					float dx = x2 - x1;
					float dy = y2 - y1;

					// 4d noise. two orthogonal 3d cylinders. Loops continuously along x and y dimensions.
					float modX = x1 + qdMod + cos(s * 2 * PI) * dx / (2 * PI / octave);
					float modY = y1 - qdMod + cos(t * 2 * PI) * dy / (2 * PI / octave);
					float modZ = x1 + qdMod + sin(s * 2 * PI) * dx / (2 * PI / octave);
					float modW = y1 - qdMod + sin(t * 2 * PI) * dy / (2 * PI / octave);

					m_xyValues.push_back(modX);
					m_xyValues.push_back(modY);
					m_xyValues.push_back(modZ);
					m_xyValues.push_back(modW);
				}
			}
		}
		octave = startOctave;
	}
	void m_initSimplex(float sizeX, float sizeY, int octaves)
	{
		OpenSimplexNoise::Noise simplex(494358);
		m_simplexOctaves = octaves;
		m_simplexSizeX = sizeX;
		m_simplexSizeY = sizeY;

		const float x{ sizeX };
		const float y{ sizeY };
		m_createSimplexValues(x, y);
		m_tempContainer.clear();

		for (int i = 0; i < x * y; i++)
		{
			double noise{ 0.0 };
			for (int j = 0; j < m_simplexOctaves; j++)
			{
				//std::cout << simplex.eval(static_cast<double>(xyValues[i + x * y * j].x), static_cast<double>(xyValues[i + x * y * j].y)) << '\n';+
				const double modX{ static_cast<double>(m_xyValues[(i * 4 + 0) + 4 * x * y * j]) };
				const double modY{ static_cast<double>(m_xyValues[(i * 4 + 1) + 4 * x * y * j]) };
				const double modZ{ static_cast<double>(m_xyValues[(i * 4 + 2) + 4 * x * y * j]) };
				const double modW{ static_cast<double>(m_xyValues[(i * 4 + 3) + 4 * x * y * j]) };

				noise += simplex.eval(modX, modY, modZ, modW) / (j + 1);

			}


			noise *= (255.999 / m_simplexOctaves); // overflow???
			int noiseInt = static_cast<int>(noise);
			m_tempContainer.push_back(noiseInt);

		}
		m_normalizeRGB();
		createSimplexTexture();
	}
	void m_normalizeRGB()
	{
		int lowest{ 0 };
		int highest{ 0 };
		for (size_t i = 0; i < m_tempContainer.size(); i++)
		{

			if (m_tempContainer[i] < lowest) { lowest = m_tempContainer[i]; }
			if (m_tempContainer[i] > highest) { highest = m_tempContainer[i]; }
		}
		//std::cout << "lowest: " << lowest << "     Highest: " << highest << '\n';
		m_simplexData.clear();
		for (size_t i = 0; i < m_tempContainer.size(); i++)
		{
			this->m_tempContainer[i] += abs(lowest);
			if (m_tempContainer[i] > 255) { m_tempContainer[i] = 255; }

			//optional clamping for water
			if (isWater)
			{
				m_tempContainer[i] = m_tempContainer[i] / 25;
				m_tempContainer[i] = m_tempContainer[i] * 25;
				if (m_tempContainer[i] > 150)
				{
					m_tempContainer[i] /= 5;
				}
				if (m_tempContainer[i] < 120)
				{
					m_tempContainer[i] *= 5;
				}
			}
			//std::cout << noiseInt << '\n';
			sf::Uint8 noiseUint = sf::Uint8(m_tempContainer[i]);
			m_simplexData.push_back(noiseUint);
		}
	}

	void createSimplexTexture()

	{
		sf::Image perlinImage;
		const int x{ intify(m_simplexSizeX) };
		const int y{ intify(m_simplexSizeY) };
		noise.setSize(sf::Vector2f(x, y));


		sf::Uint8* pixels = new sf::Uint8[x * y * 4];
		for (int i = 0; i < x * y; i++)
		{
			sf::Uint8 mutate{ m_simplexData[i] };
			pixels[(i * 4) + 0] = mutate;
			pixels[(i * 4) + 1] = mutate;
			pixels[(i * 4) + 2] = mutate;
			pixels[(i * 4) + 3] = mutate;

		}
		perlinImage.create(x, y, pixels);
		delete[] pixels;
		noiseTexture.create(x, y);
		noiseTexture.loadFromImage(perlinImage);
		noise.setTexture(&noiseTexture);

	}
	
};