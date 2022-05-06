#include <algorithm>
#include <utility>
#include "Text.h"
#include "Engine.h"
#include "FontManager.h"

using namespace ArtemisEngine;

Text::Text(std::string text, SDL_Color color, const std::string& fontName, int fontSize, const Vector2& position)
{
	this->text = std::move(text);
	this->color = color;
	this->fontSize = fontSize;
	this->position = position;

    this->font = FontManager::GetFont(fontName);

	Engine::textsToRender.push_back(this);
}

Text::~Text()
{
    if (auto find = std::find(Engine::textsToRender.begin(), Engine::textsToRender.end(), this); find != Engine::textsToRender.end())
    {
        Engine::textsToRender.erase(find);
    }
}


void Text::Render() const
{
	auto surf = TTF_RenderText_Blended (font, text.c_str(), color);
    auto tex = SDL_CreateTextureFromSurface(Engine::renderer, surf);
	SDL_FreeSurface(surf);
    auto textW = 0, textH = 0;

	SDL_QueryTexture(tex, nullptr, nullptr, &textW, &textH);
	SDL_Rect dstRect = {Vector2::cordToPixelX(position.x) - textW * fontSize / 2, Vector2::cordToPixelY(position.y) - textH * fontSize / 2, textW * fontSize, textH * fontSize };

	SDL_RenderCopy(Engine::renderer, tex, nullptr, &dstRect);

	SDL_DestroyTexture(tex);
}
