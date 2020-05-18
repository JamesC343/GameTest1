//Primarily Camera remains within the borders of the world
//Secondarily Camera centers on the Player
#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"
#include "MainWindow.h"
#include "Font.h"
#include "TerrainMap.h"
#include "TerrainObject.h"

class Camera// : public Entity
{
    public:
        Camera(MainWindow*,Graphics*,TerrainMap*,std::vector<TerrainObject*>*,Player*,std::vector<Entity*>*,RectI);
        virtual ~Camera();
        void Routine(const float);
        void DrawSprites(const float);
		void ToggleDisplayFPS();

    protected:

    private:
		void DrawEntities();
		void DrawTerrain();
		
        void Move(float);
        void SetPosition(Vector<int> newPosition);
		Vector<int> GetTopLeft();

		MainWindow* wnd;
		Graphics* gfx;
		bool displayFramesPerSecond = true;
		int ticksPerSecond = 0;
		int framesPerSecond = 0;

		const Surface* terrainMapSurface;
		Player* target;

		std::vector<Entity*>* entities;
		std::vector<TerrainObject*>* terrainObjects;
		
		Font font = "images/Fixedsys16x28.bmp";
		Surface* FPSBackGround;
		Surface* backgroundSprite;
		Surface* foregroundSprite;
		Surface* terrainSprite;
        Sprite* cursor;
		
		Vector<int> cameraSize;
		Vector<int> cameraPos;
		RectI boundary;
};

#endif // CAMERA_H
