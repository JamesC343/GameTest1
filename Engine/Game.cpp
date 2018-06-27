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

Game::Game( MainWindow& wnd ) :	wnd( wnd )
{
	gfx = new Graphics(wnd);
	
	Sprite* playerSprite = new Sprite("images/player.bmp", { 0,55,0,60 });
	player = new Player(playerSprite, { 55 * (20), 60 * (20) }, { 0 * (20), 0 * (20) });
	entities.push_back(player);

	Sprite* yorpSprite = new Sprite("images/yorp.bmp", { 0,29,0,42 });
	entities.push_back(new EntityY(yorpSprite, { 29 * (20), 42 * (20) }, { 400 * (20), 200 * (20) }));

	loadTerrainMap();

	loadDerivedSets();
	
	//camera = new Camera(&wnd, gfx, player, &entities, { 0 + 320, worldSize.x * 40 - 320, 0 + 240, worldSize.y * 32 - 240 } );
	camera = new Camera(&wnd, gfx, player, &visualObjects, { 0, worldSize.x * 40, 0, worldSize.y * 32 } );
	camera->AddTerrainMap(terrainMap, worldSize);

	physics = new Physics(player, &physicalObjects);
	physics->AddTerrainMap(terrainMap, worldSize);

	ft.Mark();
}

void Game::Go()
{
	gfx->BeginFrame();

	float deltaTime = ft.Mark();

	while(deltaTime > 1000)
	{
		UpdateModel(1000);
		deltaTime -= 1000;
	}

	UpdateModel(deltaTime);
	
	ComposeFrame();
	gfx->EndFrame();
}

void Game::UpdateModel(const float deltaTime)
{

	if( wnd.kbd.KeyIsPressed( 'A' ) )
	{
		player->Run(-100 * (20));
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		player->Run(100 * (20));
	}
	if (wnd.kbd.KeyIsPressed('P'))
	{
		int foo = 0;//BreakPoint
	}
	if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
	{
		player->Jump(-750 * (20));
	}

	for (int i = 0; i < entities.size(); i++)
		entities.at(i)->Routine(deltaTime);

	for (int i = 0; i < physicalObjects.size(); i++)
		physicalObjects.at(i)->Routine();

	physics->Routine(deltaTime);
	camera->Routine(deltaTime);
}

void Game::ComposeFrame()
{
	camera->DrawSprites();
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

	auto mapIterator = map.cbegin();
	for (int i = 0; i < worldSize.x*worldSize.y; i++, ++mapIterator)
		terrainMap[i] = (*mapIterator == 'B') ? 1 : 0;

	Sprite* thisIsAMemoryLeak = new Sprite("images/terrain2.bmp", { 0,40,0,32 });

	auto mapIterator2 = map.cbegin();
	for (int i = 0; i < worldSize.x*worldSize.y; i++, ++mapIterator2)
		if(*mapIterator2 == 'B')
			terrainObjects.push_back(new TerrainObject(thisIsAMemoryLeak, Vei2{ 40, 32 }, Vei2{ i%worldSize.x * 40 * (20), i / worldSize.x * 32 * (20) }));
}

void Game::loadDerivedSets()
{
	PhysicalObject* loadObject;

	for (int i = 0; i < entities.size(); i++)
	{
		loadObject = dynamic_cast<PhysicalObject*> (entities.at(i));

		if (loadObject != NULL)
		{
			physicalObjects.push_back(loadObject);
			visualObjects.push_back(loadObject);
		}
	}

	loadObject = nullptr;

	for (int i = 0; i < terrainObjects.size(); i++)
	{
		loadObject = dynamic_cast<PhysicalObject*> (terrainObjects.at(i));

		if (loadObject != NULL)
			physicalObjects.push_back(loadObject);
			//visualObjects.push_back(loadObject);
	}
}
