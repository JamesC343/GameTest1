#include "RectI.h"

RectI::RectI( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

RectI::RectI( const Vei2& topLeft,const Vei2 & bottomRight )
	:
	RectI( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

RectI::RectI( const Vei2& topLeft,int width,int height )
	:
	RectI( topLeft,topLeft + Vei2( width,height ) )
{
}

void RectI::move(Vei2 move)
{
	left += move.x;
	right += move.x;
	top += move.y;
	bottom += move.y;
}

bool RectI::IsOverlappingWith( const RectI& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectI::IsContainedBy( const RectI & other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

bool RectI::Contains( const Vei2& point ) const
{
	return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
}

RectI RectI::FromCenter( const Vei2 & center,int halfWidth,int halfHeight )
{
	const Vei2 half( halfWidth,halfHeight );
	return RectI( center - half,center + half );
}

RectI RectI::GetExpanded( int offset ) const
{
	return RectI( left - offset,right + offset,top - offset,bottom + offset );
}

Vei2 RectI::GetCenter() const
{
	return Vei2( (left + right) / 2,(top + bottom) / 2 );
}

Vei2 RectI::getTopLeft()
{
	return { left, top };
}

int RectI::GetWidth() const
{
	return right - left + 1;
}

int RectI::GetHeight() const
{
	return bottom - top + 1;
}

int RectI::GetMinRadius() const
{
	return sqrt(GetWidth() * GetWidth() + GetHeight() * GetHeight()) / 2;
}
