#include "Input.h"
#include "ArtemisEngine.h"

bool Input::GetKeyDown(SDL_Keycode key)
{
	if (ArtemisEngine::event.type == SDL_KEYDOWN && ArtemisEngine::event.key.keysym.sym == key)
	{
		return  true;
	}

	return false;
}

bool Input::GetKeyUp(SDL_Keycode key)
{
	if (ArtemisEngine::event.type == SDL_KEYUP && ArtemisEngine::event.key.keysym.sym == key)
	{
		return  true;
	}

	return false;
}
