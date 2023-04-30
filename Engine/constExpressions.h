#pragma once
template <typename T>
constexpr float floatify(T const& value) { return static_cast<float>(value); }
constexpr unsigned int MAP_WIDTH{ 768 };
constexpr unsigned int MAP_HEIGHT{ 448 };
constexpr int MAP_SIZE{ 336 };