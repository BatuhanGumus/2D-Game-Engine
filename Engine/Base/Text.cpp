#include "Text.h"
#include "Engine.h"
#include "FontManager.h"

using namespace ArtemisEngine;

Text::Text(std::string _text, SDL_Color _color, std::string _fontName, int _fontSize, Vector2 _position)
{
	this->text = _text;
	this->color = _color;
	this->fontSize = _fontSize;
	this->position = _position;

	for (int i = 0; i < FontManager::fonts.size(); i++)
	{
		if (_fontName == FontManager::fonts[i].name)
		{
			font = FontManager::fonts[i].file;
			break;;
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
