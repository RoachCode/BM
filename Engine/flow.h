#pragma once
#include <SFML/Graphics.hpp>
// #include "particles.h" - circular linkage. removed, nothing broken...?
#include "OpenSimplexNoise.h"
#include "constExpressions.h"
#include <deque>

extern class Flow : public sf::Drawable, public sf::Transformable
{
private:
	bool drawGrid;
	bool drawNeedles;
	bool drawLines;

	sf::Image image;
	sf::Texture gradient;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	sf::CircleShape tracer;
	sf::Vector2u tileSize;
	sf::RectangleShape line;
	sf::Vector2u gridSize;
	std::vector<float> angleVector;

	// boolean access
	bool queryDrawGrid();
	bool queryDrawNeedles();
	bool queryDrawLines();
	void toggleDrawGrid();
	void toggleDrawNeedles();
	void toggleDrawLines();
	void toggleDrawGrid(bool update);
	void toggleDrawNeedles(bool update);
	void toggleDrawLines(bool update);

	std::string currentName;
	unsigned int width;
	unsigned int height;
	sf::VertexArray m_vertices;


	float simplexSizeX;
	float simplexSizeY;
	std::deque<sf::Uint8> simplexData;
	int simplexOctaves;
	std::vector<float> xyValues;
	std::vector<int> tempContainer;

	Flow();

	void createSimplexValues(int x, int y);

	void initSimplex(float sizeX, float sizeY, int octaves);
	void normalizeRGB();
};



//float red;
//float green;
//float blue;
//float alpha - transparency;
//int plottedPoints - how many points to plot before moving to the next xCount; ie, how long the "line" that gets drawn is
//float stepSize - how far to move between calls to draw; (fineness of line - big numbers lead to dotted lines)
//int xCount - number of start points to create, wide
//int yCount - number of start points to create, high
//bool granularDisplay - slow display but shows more frames
extern class FlowPreset
{
public:
	int name;
	float red;
	float green;
	float blue;
	float alpha;

	int plottedPoints;
	int ppCounter{ 0 };
	float stepSize;

	int xCount;
	int yCount;

	FlowPreset() : name(-1), red(0), green(0), blue(255), alpha(255), plottedPoints(20), stepSize(100), xCount(2), yCount(2) {};
	FlowPreset(int n, float r, float g, float b, float a, int pp, float ss, int xcount, int ycount);

	void applyChanges(Flow& fl);
};

