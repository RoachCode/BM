#pragma once
#include <SFML/Graphics.hpp>

// Static casts values, saving fingers
template <typename T>
constexpr float floatify(T const& value) { return static_cast<float>(value); }

template <typename T>
constexpr int intify(T const& value) { return static_cast<int>(value); }

template <typename T>
constexpr sf::Vector2f pairF(T const& value1, T const& value2) { return sf::Vector2f(static_cast<float>(value1), static_cast<float>(value2)); }

template <typename T>
constexpr sf::Vector2i pairI(T const& value1, T const& value2) { return sf::Vector2i(static_cast<int>(value1), static_cast<int>(value2)); }

template <typename T>
constexpr sf::Vector2u pairU(T const& value1, T const& value2) { return sf::Vector2u(static_cast<unsigned int>(value1), static_cast<unsigned int>(value2)); }

// Constants
// PI
constexpr double PI{ 3.14159265358979323846264338 };

// The width of each map chunk in pixels
const unsigned int CHUNK_WIDTH_PIXELS{ 768 };

// The height of each map chunk in pixels
const unsigned int CHUNK_HEIGHT_PIXELS{ 448 };

// How many tiles wide the map chunk is
const unsigned int TILES_PER_CHUNK_X{ 24 };

// How many tiles tall the map chunk is
const unsigned int TILES_PER_CHUNK_Y{ 14 };

// Total number of tile elements per map chunk (for array size)
const unsigned int TILES_PER_CHUNK_COUNT{ 336 };

// The length/width in pixels of each tile
const unsigned int TILE_SIZE{ 32 };

// Area the tilemaps are showing
const enum Location
{
	WestKagar
};

// General direction enum
const enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UL,
	UR,
	DL,
	DR
};

// Names of flow presets for switch statement. Will remove as it's ugly and magic.
const enum FlowPresetNames
{
	InProgress,
	DragonFlame,
	CyanRivers
};