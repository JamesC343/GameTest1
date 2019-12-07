#include "RectI.h"

RectI::RectI( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

RectI::RectI( const Vector<int>& topLeft,const Vector<int> & bottomRight )
	:
	RectI( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

RectI::RectI( const Vector<int>& topLeft,int width,int height )
	:
	RectI( topLeft,topLeft + Vector<int>( width,height ) )
{
}

void RectI::Move(Vector<int> move)
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

bool RectI::Contains( const Vector<int>& point ) const
{
	return point.x >= left && point.x < right && point.y >= top && point.y < bottom;
}

RectI RectI::FromCenter( const Vector<int> & center,int halfWidth,int halfHeight )
{
	const Vector<int> half( halfWidth,halfHeight );
	return RectI( center - half,center + half );
}

RectI RectI::GetExpanded( int offset ) const
{
	return RectI( left - offset,right + offset,top - offset,bottom + offset );
}

Vector<int> RectI::GetCenter() const
{
	return Vector<int>( (left + right) / 2,(top + bottom) / 2 );
}

Vector<int> RectI::GetBottomCenter() const
{
	return Vector<int>((left + right) / 2, bottom);
}

Vector<int> RectI::getTopLeft()
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
