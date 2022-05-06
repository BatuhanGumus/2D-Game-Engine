#pragma once

#include <string>
#include "Vector2.h"
#include "Color.h"

namespace ArtemisEngine
{
    class Debug
    {
    public:

        enum LogType
        {
            Message = 1,
            Warning = 2,
            Error = 3
        };

        static void Log(const std::string &text, LogType type = Message);
        static void DrawLine(const Vector2* p1, const Vector2* p2, const Color* color = new Color(255, 0, 0, 255));

        static bool DrawColliders;
    };
}

