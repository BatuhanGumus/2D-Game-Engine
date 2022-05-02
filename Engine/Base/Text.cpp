#include "Text.h"
#include "Engine.h"
#include "FontManager.h"

using namespace ArtemisEngine;

Text::Text(std::string text, SDL_Color color, std::string fontName, int fontSize, Vector2 position)
{
	this->text = text;
	this->color = color;
	this->fontSize = fontSize;
	this->position = position;

	for (int i = 0; i < FontManager::fonts.size(); i++)
	{
		if (fontName == FontManager::fonts[i].name)
		{
			font = FontManager::fonts[i].file;
			break;
		}
	}

	Engine::textsToRender.push_back(this);
}

Text::~Text()
{
	for (int i = 0; i < Engine::textsToRender.size(); i++)
	{
		if (this == Engine::textsToRender[i])
		{
			Engine::textsToRender.erase(Engine::textsToRender.begin() + i);
			break;
		}
	}
}


void Text::Render()
{
	SDL_Surface* surf = TTF_RenderText_Blended (font, text.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, surf);
	SDL_FreeSurface(surf);
	int textW = 0, textH = 0;

	SDL_QueryTexture(tex, NULL, NULL, &textW, &textH);
	SDL_Rect dstrect = {Vector2::cordToPixelX(position.x) - textW * fontSize / 2, Vector2::cordToPixelY(position.y) - textH * fontSize / 2, textW * fontSize, textH * fontSize };

	SDL_RenderCopy(Engine::renderer, tex, NULL, &dstrect);

	SDL_DestroyTexture(tex);
}
