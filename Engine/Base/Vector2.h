#pragma once

namespace ArtemisEngine
{
    class Vector2
    {
    public:
        Vector2();
        Vector2(double x, double y);
        Vector2(const Vector2& copyVec);

        double x, y;

        static int CordToPixelX(double cord);
        static int CordToPixelY(double cord);

        static double Distance(const Vector2& p1, const Vector2& p2);
        static Vector2& Normalize(Vector2& vec);
        static double Magnitude(Vector2& vec);

        Vector2& Add(const Vector2& vec);
        Vector2& Subtract(const Vector2& vec);

        Vector2& operator + (const Vector2  &v2) const;
        Vector2& operator += (const Vector2  &v2);
        Vector2& operator += (double val);

        Vector2& operator - (const Vector2 &v2) const;
        Vector2& operator -= (const Vector2 &v2);
        Vector2& operator -= (double val);

        Vector2& operator / (double divider) const;
        Vector2& operator * (double multiplier) const;

        Vector2& operator = (const Vector2 &v2);
        Vector2& operator = (double value);
    };


}

