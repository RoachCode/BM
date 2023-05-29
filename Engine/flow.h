#pragma once
#include <SFML/Graphics.hpp>
#include "OpenSimplexNoise.h"
#include "constExpressions.h"
#include <deque>

extern class FlowPreset
{
public:
	// Constructor
	FlowPreset() : name(-1), red(0), green(0), blue(255), alpha(255), plottedPoints(20), stepSize(100), xCount(2), yCount(2) {};
	FlowPreset(int n, float r, float g, float b, float a, int pp, float ss, int xcount, int ycount);

	// Preset name
	int name;

	// Color
	float red;
	float green;
	float blue;
	float alpha;

	// Variables
	int plottedPoints;
	int ppCounter{ 0 };
	float stepSize;

	// Number of start point seeds
	int xCount;
	int yCount;
};

extern class Flow
{
public:
	// Constructor
	Flow();
	// Logic that draws to flowWindowTexture then flowWindow
	void drawFlow(FlowPreset& fp);

	// Width and height of flow cells in pixels
	sf::Vector2u tileSize;
	// Size of the drawable area, truncating the edges created by floating point errors
	sf::Vector2u gridSize;
	// Texture that holds the flow texture
	sf::RenderTexture flowWindowTexture;
	// RectangleShape that acts as a display surface for the flowWindowTexture
	sf::RectangleShape flowWindow;
	// Vector array of angles, one per cell
	std::vector<float> angleVector;
	// Name of the currently loaded FlowPreset
	std::string currentName;

private:

	// Iterates on the current flow algorithm
	void m_applyChanges(FlowPreset& fp);
	// Creates simplex values for flow
	void m_createSimplexValues(int x, int y);
	// Initializes simplex
	void m_initSimplex(float sizeX, float sizeY, int octaves);
	// Averages value to a clamp with squashing
	void m_normalizeRGB();
	// Internal draw call for m_applyChanges iteration
	void m_drawAllLines(FlowPreset& fp);

	// Behaviour
	bool m_drawGrid;
	bool m_drawNeedles;
	bool m_drawLines;
	int m_simplexOctaves;

	// Size
	unsigned int m_width;
	unsigned int m_height;
	float m_simplexSizeX;
	float m_simplexSizeY;

	// Resources
	sf::Texture m_gradient;
	sf::CircleShape m_tracer;
	sf::RectangleShape m_line;
	sf::VertexArray m_vertices;

	// Data
	std::vector<float> m_xyValues;
	std::vector<int> m_tempContainer;
	std::deque<sf::Uint8> m_simplexData;
};
