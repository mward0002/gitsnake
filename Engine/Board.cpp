#include "Board.h"
#include <assert.h>
Board::Board(Graphics& gfx)
	:
	gfx ( gfx )
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension - 2, dimension - 2, c);
}

void Board::DrawBorderCell(const Location& loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension , dimension, c);
}

void Board::DrawBorder()
{
	for (int x = startX; x <= width; x++) {
		Location loc = { x, height};
		DrawBorderCell(loc, borderColor);
	}
	for (int y = startY; y <= height; y++) {
		Location loc = { width, y };
		DrawBorderCell(loc, borderColor);
	}
	for (int x = startX; x <= width; x++) {
		Location loc = { x, startY - 1 };
		DrawBorderCell(loc, borderColor);
	}
	for (int y = startY -1; y <= height; y++) {
		Location loc = { startX - 1, y };
		DrawBorderCell(loc, borderColor);
	}
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetStartX() const
{
	return startX;
}

int Board::GetStartY() const
{
	return startY;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= startX && loc.x < width && loc.y >= startY && loc.y < height; ;
}
