//Primarily Camera remains within the borders of the world
//Secondarily Camera centers on the Player
#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"
#include "MainWindow.h"

class Camera// : public Entity
{
    public:
        Camera(MainWindow*,Graphics*,Player*,std::vector<PhysicalObject*>*,RectI);
        virtual ~Camera();
        void Routine(float);
        void DrawSprites();
		void AddTerrainMap(int*,Vei2);

    protected:

    private:
		void DrawEntities();
		void DrawTerrain();
		
        void Move(float);
        void SetPosition(Vei2 newPosition);
		Vei2 GetTopLeft();

		MainWindow* wnd;
		Graphics* gfx;
		Player* target;

		std::vector<PhysicalObject*>* visualObjects;
		
		Surface* backgroundSprite;
		Surface* terrainSprite;
        Sprite* cursor;
		
		Vei2 cameraSize;
		Vei2 cameraPos;
		RectI boundary;

		int* terrainMap;
		Vei2 worldSize;
};

#endif // CAMERA_H
