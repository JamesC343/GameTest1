#pragma once
#include <cmath>

template<typename T>
class Vector
{
public:
	Vector() = default;
	Vector(T x_in, T y_in)
		: x(x_in), y(y_in)
	{}
	Vector(const Vector<int>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{}
	Vector(const Vector<float>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{}
	Vector operator+(const Vector& rhs) const
	{
		return Vector(x + rhs.x, y + rhs.y);
	}
	Vector& operator+=(const Vector& rhs)
	{
		return *this = *this + rhs;
	}
	Vector operator*(T rhs) const
	{
		return Vector(x * rhs, y * rhs);
	}
	Vector& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vector operator-(const Vector& rhs) const
	{
		return Vector(x - rhs.x, y - rhs.y);
	}
	Vector& operator-=(const Vector& rhs)
	{
		return *this = *this - rhs;
	}
	Vector operator/(T rhs) const
	{
		return Vector(x / rhs, y / rhs);
	}
	Vector& operator/=(T rhs)
	{
		return *this = *this / rhs;
	}
	T GetLength() const
	{
		return std::sqrt(T(GetLengthSq()));
	}
	int GetLengthSq() const
	{
		return x * x + y * y;
	}
	bool IsZero() const
	{
		if (x != 0 || y != 0)
			return true;

		return false;
	}
public:
	T x;
	T y;
};

