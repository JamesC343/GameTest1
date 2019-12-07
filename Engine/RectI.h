#pragma once

#include "Vector.h"
#include <cmath>

class RectI
{
public:
	RectI() = default;
	RectI( int left_in,int right_in,int top_in,int bottom_in );
	RectI( const Vector<int>& topLeft,const Vector<int>& bottomRight );
	RectI( const Vector<int>& topLeft,int width,int height );
	void Move(Vector<int>);
	bool IsOverlappingWith( const RectI& other ) const;
	bool IsContainedBy( const RectI& other ) const;
	bool Contains( const Vector<int>& point ) const;
	static RectI FromCenter( const Vector<int>& center,int halfWidth,int halfHeight );
	RectI GetExpanded( int offset ) const;
	Vector<int> GetCenter() const;
	Vector<int> GetBottomCenter() const;
	Vector<int> getTopLeft();
	int GetWidth() const;
	int GetHeight() const;
	int GetMinRadius() const;
public:
	int left;
	int right;
	int top;
	int bottom;
};