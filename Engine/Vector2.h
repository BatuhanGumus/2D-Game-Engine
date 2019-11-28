#pragma once
class Vector2
{
public:
	Vector2(double x, double y);
	Vector2(const Vector2& copyVec);

	double x, y;

	static int cordToPixelX(double cord);
	static int cordToPixelY(double cord);

	Vector2& Add(const Vector2& vec);
	Vector2& Subtract(const Vector2& vec);

	Vector2& operator + (const Vector2  &v2);
	Vector2& operator += (const Vector2  &v2);

	Vector2& operator - (const Vector2 &v2);
	Vector2& operator -= (const Vector2 &v2);

	Vector2& operator / (const double divider);
	Vector2& operator * (const double multiplier);

	Vector2& operator = (const Vector2 &v2);
};

