#pragma once
#include "Board.h"
#include "Location.h"
class Snake
{
private:
	class Segment 
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(const Color color);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_location);
		void Draw(Board& brd) const;
		
		const Location& GetLocation() const;
	private: 
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	int GetSpeed();
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;


private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int speed = 40;
	int nSegments = 1;
	int minusGreen = 0;
	int multiplier = -1;
	int posNeg = 1;
	int factor = 70;
};