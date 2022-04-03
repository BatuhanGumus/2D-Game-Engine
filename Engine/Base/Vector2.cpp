#include "Vector2.h"
#include "ArtemisEngine.h"
#include <iostream>
#include <math.h>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& copyVec)
{
	this->x = copyVec.x;
	this->y = copyVec.y;
}

int Vector2::cordToPixelX(double cord)
{
	return  cord * ArtemisEngine::pixW / 8 + ArtemisEngine::pixW / 2;
}

int Vector2::cordToPixelY(double cord)
{
	return  ArtemisEngine::pixH / 2 - cord * ArtemisEngine::pixH / 6;
}

double Vector2::Distance(const Vector2& p1, const Vector2& p2)
{
	double xLen = p1.x - p2.x;
	double yLen = p1.y - p2.y;
	return sqrt(xLen * xLen + yLen * yLen);
}

Vector2& Vector2::Normalize(Vector2& vec)
{
	double len = sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec / len;
}

double Vector2::Magnitude(Vector2& vec)
{
	return  sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vector2& Vector2::Add(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2& Vector2::operator + (const Vector2 &v2)
{
	return *new Vector2(this->x + v2.x, this->y + v2.y);
}

Vector2& Vector2::operator += (const Vector2 &v2)
{
	return this->Add(v2);
}

Vector2& Vector2::operator+=(double val)
{
	this->x += val;
	this->y += val;
	return *this;
}

Vector2& Vector2::operator - (const Vector2 &v2)
{
	return *new Vector2(this->x - v2.x, this->y - v2.y);
}

Vector2& Vector2::operator -= (const Vector2 &v2)
{
	return this->Subtract(v2);
}

Vector2& Vector2::operator-=(double val)
{
	this->x -= val;
	this->y -= val;
	return *this;
}

Vector2& Vector2::operator / (const double divider)
{
	return *new Vector2(this->x / divider, this->y / divider);
}

Vector2& Vector2::operator * (const double multiplier)
{
	return *new Vector2(this->x * multiplier, this->y * multiplier);
}

Vector2& Vector2::operator = (const Vector2& v2)
{
	this->x = v2.x;
	this->y = v2.y;
	return *this;
}

Vector2& Vector2::operator=(double value)
{
	this->x = value;
	this->y = value;
	return *this;
}
