#include "TextureManager.h"
#include "Engine.h"
#include "SDL_image.h"

using namespace ArtemisEngine;

SDL_Texture* TextureManager::LoadText(const char* fileName)
{
	SDL_Surface* tmpSurf = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Engine::renderer, tex, &src, &dest);
}
