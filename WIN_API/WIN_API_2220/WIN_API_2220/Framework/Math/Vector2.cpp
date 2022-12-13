#include "framework.h"
#include "Vector2.h"

Vector2::Vector2()
: x(0)
, y(0)
{
}

Vector2::Vector2(float x, float y)
: x(x)
, y(y)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

bool Vector2::operator<(const Vector2& other) const
{
	return this->Length() < other.Length();
}

bool Vector2::operator>(const Vector2& other) const
{
	return this->Length() > other.Length();
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;

	return (*this);
}

Vector2& Vector2::operator++()
{
	++x;
	++y;

	return (*this);
}

Vector2 Vector2::operator++(int)
{
	Vector2 temp = *this;

	++x;
	++y;

	return temp;
}

float Vector2::Length() const
{
	return sqrt(powf(x, 2) + powf(y, 2));
}

