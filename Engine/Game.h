/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include <vector>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Player.h"
#include "EntityY.h"
#include "TerrainObject.h"
#include "Physics.h"
#include "Camera.h"
#include "FrameTimer.h"
#include "TerrainMap.h"

class Game
{
	public:
		Game( class MainWindow& wnd );
		Game( const Game& ) = delete;
		Game& operator=( const Game& ) = delete;
		void Go();
	
	private:
		void ComposeFrame(const float);
		void UpdateModel(const float);
	
	private:
		MainWindow& wnd;
		Graphics* gfx;
		Physics* physics;
		FrameTimer physicsTimer;
		FrameTimer frameTimer;

		float deltaTime = 0;
		float residualDeltaTime = 0;
		const float maximumTickTime = (1.0 / 100.0);//Would be best to keep this close to a value of a realistic FPS, otherwise it looks funny due to the character moving before the frame has been drawn
													//In an ideal world my physics would handle 'forces' such as gravity more dynamically so that I don't get strange behaviour from a non static tick time
													//The question is.. How do I increase the FPS??

		Camera* camera;
		Player* player;
		//std::vector<std::vector<bool>> terrainMatrix;
		TerrainMap* terrainMap;
		
		//Primary Sets
		std::vector<Entity*> entities;
		std::vector<TerrainObject*> terrainObjects;

		//Derived Sets
		//std::vector<PhysicalObject*> physicalObjects;//For Physics
		//std::vector<PhysicalObject*> visualObjects;//For Camera
};