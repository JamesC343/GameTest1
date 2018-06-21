#include "Camera.h"
#include "MainWindow.h"

Camera::Camera(MainWindow* wnd, Graphics* gfx, Player* target, std::vector<PhysicalObject*>* visualObjects, RectI boundary)
	: wnd (wnd), gfx (gfx), boundary (boundary), target (target), visualObjects(visualObjects), cameraSize(640, 480), cameraPos(0,0)
{
	this->boundary.left += cameraSize.x / 2;
	this->boundary.right -= cameraSize.x / 2;
	this->boundary.top += cameraSize.y / 2;
	this->boundary.bottom -= cameraSize.y / 2;

	backgroundSprite = new Surface("images/background.bmp");
	terrainSprite = new Surface("images/terrain.bmp");
	cursor = new Sprite("marle32x48.bmp", { 32,64,48,96 });
}


Camera::~Camera()
{
    //dtor
}

void Camera::Routine(float deltaTime)
{
	Move(deltaTime);
}

void Camera::DrawSprites()
{
	gfx->DrawSpriteNonChroma(0, 0, *backgroundSprite);

	DrawEntities();
	DrawTerrain();

	gfx->DrawSprite(wnd->mouse.GetPosX() - 16, wnd->mouse.GetPosY() - 24, *cursor, gfx->GetScreenRect());
}

void Camera::DrawEntities()
{
	for (int i = 0; i < visualObjects->size(); i++)
	{
		PhysicalObject* visualObject = visualObjects->at(i);
		gfx->DrawSprite(
			visualObject->GetHitBox().left / (20) - GetTopLeft().x
			, visualObject->GetHitBox().top / (20) - GetTopLeft().y
			, visualObject->GetSprite()
			, gfx->GetScreenRect());
	}
}

void Camera::DrawTerrain()
{
for (int i = 0; i < worldSize.x*worldSize.y; i++)
		if (terrainMap[i] == 1)
			gfx->DrawSpriteNonChroma(i%worldSize.x * 40 - GetTopLeft().x, i/worldSize.x * 32 - GetTopLeft().y, *terrainSprite);
}

void Camera::AddTerrainMap(int* newMap, Vei2 mapSize)
{
	terrainMap = newMap;
	worldSize = mapSize;
}

void Camera::Move(float deltaTime)
{
	//To incorporate deltaTime, use the distance between the camera and the targetPosition to determine a camera speed
	//Use the camera speed, the deltaTime and the vector between the cameraPosition and the targetPosition
	//	to calculate the new position

	Vei2 cursorPosition(wnd->mouse.GetPosX() - cameraSize.x / 2, wnd->mouse.GetPosY() - cameraSize.y / 2);
	
	Vei2 targetPosition = target->GetHitBox().GetCenter() / (20) + cursorPosition;

	SetPosition((cameraPos * 3 + targetPosition) / 4);//Camera Smoothing
}

void Camera::SetPosition(Vei2 newPosition)
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

Vei2 Camera::GetTopLeft()
{
	return { cameraPos.x - cameraSize.x / 2, cameraPos.y - cameraSize.y / 2 };
}
