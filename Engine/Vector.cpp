#include "Vector.h"
#include <cmath>

Vector::Vector(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y);
}

Vector& Vector::operator+=(const Vector& rhs)
{
	return *this = *this + rhs;
}

Vector Vector::operator*(float rhs) const
{
	return Vector(x * rhs, y * rhs);
}

Vector& Vector::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(x - rhs.x, y - rhs.y);
}

Vector& Vector::operator-=(const Vector& rhs)
{
	return *this = *this - rhs;
}

Vector Vector::operator/(float rhs) const
{
	return Vector(x / rhs, y / rhs);
}

Vector& Vector::operator/=(float rhs)
{
	return *this = *this / rhs;
}

float Vector::GetLength() const
{
	return std::sqrt(float(GetLengthSq()));
}

int Vector::GetLengthSq() const
{
	return x * x + y * y;
}
