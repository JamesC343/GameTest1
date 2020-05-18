#include "Camera.h"
#include "MainWindow.h"
#include "Font.h"
#include <iostream>

Camera::Camera(MainWindow* wnd, Graphics* gfx, TerrainMap* terrainMap, std::vector<TerrainObject*>* terrainObjects, Player* target, std::vector<Entity*>* entities, RectI boundary)
	: wnd (wnd), gfx (gfx), boundary (boundary), terrainMapSurface(terrainMap->GetSurface()), terrainObjects(terrainObjects), target (target), entities(entities), cameraSize(640, 480), cameraPos(0,0)
{
	this->boundary.left += cameraSize.x / 2;
	this->boundary.right -= cameraSize.x / 2;
	this->boundary.top += cameraSize.y / 2;
	this->boundary.bottom -= cameraSize.y / 2;

	FPSBackGround = new Surface("images/FPSBackGround.bmp");
	backgroundSprite = new Surface("images/background.bmp");
	foregroundSprite = new Surface("images/foreground.bmp");
	terrainSprite = new Surface("images/terrainIcon.bmp");
	cursor = new Sprite("marle32x48.bmp", { 32,64,48,96 });
}


Camera::~Camera()
{
    //dtor
}

void Camera::Routine(float deltaTime)
{
	Move(deltaTime);

	ticksPerSecond = (int)(1.0 / deltaTime);
}

void Camera::DrawSprites(const float deltaTime)
{
	gfx->DrawSpriteNonChroma(0, 0, *backgroundSprite);
	//gfx->DrawSpriteNonChroma(0 - GetTopLeft().x, 608 - GetTopLeft().y, foregroundSprite->GetRect(), gfx->GetScreenRect(), *foregroundSprite);
	///////////////
	gfx->DrawSprite(0 - GetTopLeft().x, 0 - GetTopLeft().y, terrainMapSurface->GetRect(), gfx->GetScreenRect(), *terrainMapSurface);
	///////////////
	DrawEntities();
	DrawTerrain();

	gfx->DrawSprite(wnd->mouse.GetPosX() - 16, wnd->mouse.GetPosY() - 24, cursor, gfx->GetScreenRect());

	if (displayFramesPerSecond)
	{
		framesPerSecond = (int)(1.0 / deltaTime);

		gfx->DrawSpriteNonChroma(0, 0, *FPSBackGround);
		font.DrawText("FPS:" + std::to_string(framesPerSecond), Vector<int>({ 7, 4 }), Colors::Black, gfx);
		font.DrawText("TPS:" + std::to_string(ticksPerSecond), Vector<int>({ 7, 34 }), Colors::White, gfx);
	}
}

void Camera::DrawEntities()
{
	for (int i = 0; i < entities->size(); i++)
	{
		PhysicalObject* entity = entities->at(i);
		gfx->DrawSprite(
			entity->GetHitBox().left - GetTopLeft().x
			, entity->GetHitBox().top - GetTopLeft().y
			, entity->GetSprite()
			, gfx->GetScreenRect());

		//PhysicalObject* visualObject = visualObjects->at(i);
		//gfx->DrawSprite(
		//	visualObject->GetHitBox().left / (20) - GetTopLeft().x
		//	, visualObject->GetHitBox().top / (20) - GetTopLeft().y
		//	, visualObject->GetSprite()
		//	, gfx->GetScreenRect());
	}
}

void Camera::DrawTerrain()
{
	for (int i = 0; i < terrainObjects->size(); i++)
	{
		TerrainObject* terrainObject = terrainObjects->at(i);
		gfx->DrawSprite(
			terrainObject->GetTopLeft().x - GetTopLeft().x
			, terrainObject->GetTopLeft().y - GetTopLeft().y
			, terrainObject->GetSprite()
			, gfx->GetScreenRect()
		);


		//void DrawSprite(int x, int y, Sprite& sprite, const RectI& clip, Color chroma = Colors::Magenta);

		//DrawSprite(x, y, sprite.getRect(), clip, sprite.getSurface());
	}
}

void Camera::ToggleDisplayFPS()
{
	displayFramesPerSecond = !displayFramesPerSecond;
}

void Camera::Move(float deltaTime)
{
	//To incorporate deltaTime, use the distance between the camera and the targetPosition to determine a camera speed
	//Use the camera speed, the deltaTime and the vector between the cameraPosition and the targetPosition
	//	to calculate the new position

	Vector<int> cursorPosition(wnd->mouse.GetPosX() - cameraSize.x / 2, wnd->mouse.GetPosY() - cameraSize.y / 2);
	
	Vector<int> targetPosition = target->GetHitBox().GetCenter() + cursorPosition;

	SetPosition((cameraPos * 3 + targetPosition) / 4);//Camera Smoothing
}

void Camera::SetPosition(Vector<int> newPosition)
{
	if (newPosition.x < boundary.left)
		newPosition.x = boundary.left;
	else if (newPosition.x > boundary.right)
		newPosition.x = boundary.right;

	if (newPosition.y < boundary.top)
		newPosition.y = boundary.top;
	else if (newPosition.y > boundary.bottom)
		newPosition.y = boundary.bottom;

	cameraPos = newPosition;
}

Vector<int> Camera::GetTopLeft()
{
	return { cameraPos.x - cameraSize.x / 2, cameraPos.y - cameraSize.y / 2 };
}
