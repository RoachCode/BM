#pragma once
template <typename T>
// Static casts any value to a float
constexpr float floatify(T const& value) { return static_cast<float>(value); }

// The width of each map in pixels
const unsigned int MAP_WIDTH_PIXELS{ 768 };
// The height of each map in pixels
const unsigned int MAP_HEIGHT_PIXELS{ 448 };
// How many tiles wide the map is
const unsigned int TILES_PER_MAP_X{ 24 };
// How many tiles tall the map is
const unsigned int TILES_PER_MAP_Y{ 14 };
// Total number of tile elements per map (array size)
const unsigned int TILES_PER_MAP_COUNT{ 336 };
// The length in pixels of each side of a tile
const unsigned int TILE_SIZE{ 32 };

