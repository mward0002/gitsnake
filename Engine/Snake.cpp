#include "Snake.h"
#include <assert.h>
Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i) {
		segments[i].Follow(segments[i - 1]);
		
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		Color c(0, 190 + minusGreen, 0);
		segments[nSegments].InitBody(c);
		minusGreen = factor * multiplier;
		multiplier += -1*posNeg;
		if (nSegments % 2 == 0) {
			multiplier = -1;
			posNeg = posNeg * -1;
		}
		++nSegments;
	}
	if (speed >= 10) {
		speed = speed - 1;
	}
}

int Snake::GetSpeed()
{
	return speed;
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i) {
		segments[i].Draw(brd);
	}
}



bool Snake::IsInTileExceptEnd(const Location& target) const 
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;

}

void Snake::Segment::InitBody(const Color color)
{
	c = color;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_location)
{
	assert(abs(delta_location.x) + abs(delta_location.y) == 1);
	loc.Add(delta_location);

}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}



const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
