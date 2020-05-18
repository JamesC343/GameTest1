#pragma once

#include "Surface.h"
#include "RectI.h"
class Sprite
{
	public:
		Sprite(const std::string&, RectI);
		Sprite(const std::string&);
		~Sprite();
		Surface& getSurface();
		RectI& getRect();
	private:
		Surface surface;
		RectI rect;
};

