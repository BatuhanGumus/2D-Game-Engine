#include "TextureManager.h"
#include "ArtemisEngine.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadText(const char* fileName)
{
	SDL_Surface* tmpSurf = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ArtemisEngine::renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(ArtemisEngine::renderer, tex, &src, &dest);
}
