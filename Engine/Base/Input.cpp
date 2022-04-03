#include "Input.h"

using namespace ArtemisEngine;

std::vector<SDL_KeyboardEvent> Input::frameInput;
std::vector<SDL_Keycode> Input::heldButtons;
std::vector<SDL_Keycode> Input::lastFrame;

void Input::PassInFrameInput(SDL_KeyboardEvent keyEvent)
{
	frameInput.push_back(keyEvent);

	if (keyEvent.type == SDL_KEYDOWN)
	{
		for (int i = 0; i < heldButtons.size(); i++)
		{
			if (keyEvent.keysym.sym == heldButtons[i])
			{
				return;
			}
		}

		//std::cout << keyEvent.keysym.sym << " down" << std::endl;
		heldButtons.push_back(keyEvent.keysym.sym);
	}
	else
	{
		for (int i = 0; i < heldButtons.size(); i++)
		{
			if (keyEvent.keysym.sym == heldButtons[i])
			{
				heldButtons.erase(heldButtons.begin() + i);
				break;
			}
		}
	}
}

void Input::ClearInputBuffer()
{
	lastFrame = heldButtons;
	frameInput.clear();
}

bool Input::GetKeyDown(SDL_Keycode key)
{
	for (int i = 0; i < heldButtons.size(); i++)
	{
		if (key == heldButtons[i])
		{
			for (int j = 0; j < lastFrame.size(); j++)
			{
				if (key == lastFrame[j])
				{
					return false;
				}
			}

			return true;
		}
	}

	return false;
}

bool Input::GetKey(SDL_Keycode key)
{
	for (int i = 0; i < heldButtons.size(); i++)
	{
		if (key == heldButtons[i])
		{
			return true;
		}
	}

	return false;
}

bool Input::GetKeyUp(SDL_Keycode key)
{
	for (int i = 0; i < frameInput.size(); i++)
	{
		if (frameInput[i].type == SDL_KEYUP && key == frameInput[i].keysym.sym)
		{
			return true;
		}
	}

	return false;
}
