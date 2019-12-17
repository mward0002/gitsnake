/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Snake.h"
#include "SpriteCodex.h"
#include "Goal.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek({ 5,5 }),
	rng( std::random_device()()),
	goal(rng,brd,snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsOver) {
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1 ,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isStarted = true;
		}
		++snekMoveCounter;
		++addObstacleCounter;
		if (snekMoveCounter >= snek.GetSpeed()) {
			snekMoveCounter = 0;
			Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || 
				snek.IsInTileExceptEnd(next) ) {
				gameIsOver = true;
			}
			else {
				bool eating = next == goal.GetLoation();
				if (eating) {
					snek.Grow();
					
				}
				if (isStarted) {
					snek.MoveBy(delta_loc);
			}
				
				if (eating) {
					goal.Respawn(rng, brd, snek);
				}
			}

			bool hittingObstacle = false;
			for (int i = 0; i < numObstacles; i++) {

				if (obstacles[i].GetLocation() == next) {
					hittingObstacle = true;
				}
				if (hittingObstacle) {
					gameIsOver = true;
				}
			}
		}
		if (addObstacleCounter >= 1000)
		{
			addObstacleCounter = 0;
			obstacles[numObstacles].Init(rng, brd);
			numObstacles++;
		}
	}
}

void Game::ComposeFrame()
{
	if (isStarted) 
	{
		snek.Draw(brd);
		goal.Draw(brd);
		brd.DrawBorder();
		for (int i = 0; i < numObstacles; i++) {
			obstacles[i].Draw(brd);

		}
	}
	else {
		SpriteCodex::DrawTitle(200, 200, gfx);
	}

	if (gameIsOver) 
	{
		SpriteCodex::DrawGameOver(200, 200, gfx);
	}
}
