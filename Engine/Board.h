#pragma once
#include "Graphics.h"
#include "Location.h"
class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorderCell(const Location& loc, Color c);
	void DrawBorder();
	
	int GetGridHeight() const;
	int GetGridWidth() const;
	int GetStartX() const;
	int GetStartY() const;
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr int startX = 3;
	static constexpr int startY = 3;
	static constexpr Color borderColor = Colors::Gray;
	Graphics& gfx;
};