#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string& filename, RectI rect)
	: surface ( filename ), rect ( rect )
{
}

Sprite::Sprite(const std::string & filename)
	: surface(filename)
{
	rect = { 0, surface.GetWidth(), 0, surface.GetHeight() };
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
