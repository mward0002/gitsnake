#include "Obstacle.h"




void Obstacle::Init(std::mt19937& rng, Board& brd)
{
	std::uniform_int_distribution<int> yDist(brd.GetStartX() + 1, brd.GetGridHeight() - 1);
	std::uniform_int_distribution<int> xDist(brd.GetStartY() + 1, brd.GetGridWidth() - 1);
	Location newLoc;
	
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	loc = newLoc;
}

void Obstacle::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Obstacle::GetLocation()
{
	return loc;
}
