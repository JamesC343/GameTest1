#include "Sprite.h"


Sprite::Sprite(const std::string& filename, RectI rect) : surface ( filename ), rect ( rect )
{
}

Sprite::~Sprite()
{
}

Surface& Sprite::getSurface()
{
	return surface;
}

RectI& Sprite::getRect()
{
	return rect;
}
