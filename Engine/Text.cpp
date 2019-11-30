#include "Text.h"
#include "FontManager.h"
#include "ArtemisEngine.h"

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

	ArtemisEngine::textsToRender.push_back(this);
}

Text::~Text()
{
	for (int i = 0; i < ArtemisEngine::textsToRender.size(); i++)
	{
		if (this == ArtemisEngine::textsToRender[i])
		{
			ArtemisEngine::textsToRender.erase(ArtemisEngine::textsToRender.begin() + i);
			break;
		}
	}
}


void Text::Render()
{
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ArtemisEngine::renderer, surf);
	SDL_FreeSurface(surf);
	int textW = 0, textH = 0;

	SDL_QueryTexture(tex, NULL, NULL, &textW, &textH);
	SDL_Rect dstrect = {Vector2::cordToPixelX(position.x) - textW / 2, Vector2::cordToPixelY(position.y) - textH / 2, textW, textH };

	SDL_RenderCopy(ArtemisEngine::renderer, tex, NULL, &dstrect);

	SDL_DestroyTexture(tex);
}
