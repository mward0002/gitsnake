#pragma once
#include "Board.h"
#include "Location.h"
#include <random>
class Obstacle
{
public:
	void Init(std::mt19937& rng, Board& brd);
	void Draw(Board& brd) const;
	Location GetLocation();
private:
	Location loc;
	static constexpr Color c = Colors::Gray;
};