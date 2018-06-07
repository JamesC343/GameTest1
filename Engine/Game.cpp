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
#include "player.h"
#include "entityY.h"
#include "String.h"
#include "Camera.h"

Game::Game( MainWindow& wnd ) :	wnd( wnd )
{
	gfx = new Graphics(wnd);
	
	player = new Player("images/player.bmp", { 0,55,0,60 }, { 55 * (20), 60 * (20) }, { 0 * (20), 0 * (20) });

	entities.push_back(player);
	entities.push_back(new EntityY("images/yorp.bmp", { 0,29,0,42 }, { 29 * (20), 42 * (20) }, { 400 * (20), 200 * (20) }));

	loadTerrainMap();
	
	//camera = new Camera(&wnd, gfx, player, &entities, { 0 + 320, worldSize.x * 40 - 320, 0 + 240, worldSize.y * 32 - 240 } );
	camera = new Camera(&wnd, gfx, player, &entities, { 0, worldSize.x * 40, 0, worldSize.y * 32 } );
	camera->addTerrainMap(terrainMap, worldSize);

	physics = new Physics(player, &entities);
	physics->addTerrainMap(terrainMap, worldSize);

	ft.Mark();
}

void Game::Go()
{
	gfx->BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx->EndFrame();
}

void Game::UpdateModel()
{
	const float deltaTime = ft.Mark();

	if( wnd.kbd.KeyIsPressed( 'A' ) )
	{
		player->run(-100 * (20));
	}
	if( wnd.kbd.KeyIsPressed( 'D' ) )
	{
		player->run(100 * (20));
	}
	if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
	{
		player->jump(-500 * (20));
	}
	
	for (int i = 0; i < entities.size(); i++)
		entities.at(i)->routine(deltaTime);

	physics->routine(deltaTime);
	camera->routine(deltaTime);
}

void Game::ComposeFrame()
{
	camera->drawSprites();
}

void Game::loadTerrainMap()
{
	std::string map =
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB"
		"BAAAAAAAAABAAAAAAAAAAAAAAAAAAAAB"
		"BAAAAAAAAAAAAAABBBBBBBBAAAAAAAAB"
		"BBBAAAAAAAAAABBBBBBBBBBBAAAAABBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";

	auto mi = map.cbegin();
	for (int i = 0; i < worldSize.x*worldSize.y; i++, ++mi)
			terrainMap[i] = (*mi == 'B') ? 1 : 0;
}
