#include <algorithm>
#include "Input.h"

using namespace ArtemisEngine;

std::vector<SDL_KeyboardEvent> Input::_frameInput;
std::vector<SDL_Keycode> Input::_heldButtons;
std::vector<SDL_Keycode> Input::_lastFrame;

void Input::PassInFrameInput(SDL_KeyboardEvent keyEvent)
{
	_frameInput.push_back(keyEvent);

	if (keyEvent.type == SDL_KEYDOWN)
	{
        if (!(std::find(_heldButtons.begin(), _heldButtons.end(), keyEvent.keysym.sym) != _heldButtons.end()))
        {
            _heldButtons.push_back(keyEvent.keysym.sym);
        }
	}
	else
	{
        if (auto found = std::find(_heldButtons.begin(), _heldButtons.end(), keyEvent.keysym.sym); found != _heldButtons.end())
        {
            _heldButtons.erase(found);
        }
	}
}

void Input::ClearInputBuffer()
{
	_lastFrame = _heldButtons;
	_frameInput.clear();
}

bool Input::GetKeyDown(SDL_Keycode key)
{
    if (std::find(_heldButtons.begin(), _heldButtons.end(), key) != _heldButtons.end())
    {
        if (std::find(_lastFrame.begin(), _lastFrame.end(), key) != _lastFrame.end())
        {
            return false;
        }

        return true;
    }

	return false;
}

bool Input::GetKey(SDL_Keycode key)
{
    if (std::find(_heldButtons.begin(), _heldButtons.end(), key) != _heldButtons.end())
    {
        return true;
    }

	return false;
}

bool Input::GetKeyUp(SDL_Keycode key)
{
	for (int i = 0; i < _frameInput.size(); i++)
	{
		if (_frameInput[i].type == SDL_KEYUP && key == _frameInput[i].keysym.sym)
		{
			return true;
		}
	}

	return false;
}
