#include "Debug.h"
#include <iostream>
#include "Engine.h"
#include "Transform.h"

void Debug::Log(std::string text, LogType type)
{
    std::string typeText = "";

    if (type == Message)  typeText = "Message";
    else if(type == Warning) typeText = "!Warning";
    else if(type == Error) typeText = "!!!Error";
    else typeText = "_";

    std::cout << typeText << ": " << text << std::endl;
}

void Debug::DrawLine(const Vector2* p1, const Vector2* p2, const Color* color)
{
    Color* prevColor = new Color();

    SDL_GetRenderDrawColor(Engine::renderer, &prevColor->r, &prevColor->g, &prevColor->b, &prevColor->a);

    SDL_SetRenderDrawColor(Engine::renderer, color->r, color->g, color->b, color->a);

    int ret = SDL_RenderDrawLine(Engine::renderer,
                                 Vector2::cordToPixelX(p1->x),
                                 Vector2::cordToPixelY(p1->y),
                                 Vector2::cordToPixelX(p2->x),
                                 Vector2::cordToPixelY(p2->y));

    if (ret < 0) Log(SDL_GetError(), Warning);

    SDL_SetRenderDrawColor(Engine::renderer, prevColor->r, prevColor->g, prevColor->b, prevColor->a);
}
