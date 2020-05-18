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
#include "Player.h"
#include "EntityY.h"
#include "String.h"
#include "Camera.h"
#include <iostream>

Game::Game(MainWindow& wnd) : wnd(wnd)
{
	gfx = new Graphics(wnd);

	Sprite* playerSprite = new Sprite("images/player.bmp");
	player = new Player(playerSprite, { 0, 0 }, { 55, 60 }, "Player");
	entities.push_back(player);

	Sprite* yorpSprite = new Sprite("images/yorp.bmp");
	//entities.push_back(new EntityY(yorpSprite, { 400 * (10), 200 * (10) }, { 29 * (10), 42 * (10) }, "Yorp"));

	Surface* terrainSurface = new Surface("images/terrain.bmp");
	terrainMap = new TerrainMap(terrainSurface);

	terrainObjects.push_back(new TerrainObject(new Sprite("images/terrainObject.bmp"), { 990, 360 }));
	terrainObjects.push_back(new TerrainObject(new Sprite("images/terrainObject2.bmp"), { 200, 552 }));

	const Vector<int> worldSize = { 32,24 }; //Legacy?
	
	camera = new Camera(&wnd, gfx, terrainMap, &terrainObjects, player, &entities, { 0, worldSize.x * 40, 0, worldSize.y * 32 } );
	physics = new Physics(player, terrainMap, &terrainObjects, &entities);

	physicsTimer.Mark();
	frameTimer.Mark();
}

void Game::Go()
{
	gfx->BeginFrame();

	float deltaTime = physicsTimer.Mark() + residualDeltaTime;

	while(deltaTime > maximumTickTime)
	{
		UpdateModel(maximumTickTime);
		deltaTime -= maximumTickTime;
	}

	residualDeltaTime = deltaTime;
	
	ComposeFrame(frameTimer.Mark());
	gfx->EndFrame();
}

void Game::UpdateModel(const float deltaTime)
{
	if (wnd.kbd.KeyIsPressed( VK_RETURN ))
	{
		camera->ToggleDisplayFPS();
		//std::cout << "Player Height: " << player->GetHitBox().GetCenter().y << "\n";

		/*std::string test;

		printf("WTF");
		std::cout << " - ";
		std::cin >> test;*/
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		player->Run(-25);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		player->Run(25);
	}
	if (wnd.kbd.KeyIsPressed('P'))
	{
		int foo = 0;//BreakPoint
	}
	if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
	{
		player->Jump(-850);
	}

	for (int i = 0; i < entities.size(); i++)
		entities.at(i)->Routine(deltaTime);

	physics->Routine(deltaTime);
	camera->Routine(deltaTime);
}

void Game::ComposeFrame(const float deltaTime)
{
	camera->DrawSprites(deltaTime);
}