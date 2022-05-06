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
    auto isHeld = std::find(_heldButtons.begin(), _heldButtons.end(), key) != _heldButtons.end();
    auto wasHeld = std::find(_lastFrame.begin(), _lastFrame.end(), key) != _lastFrame.end();
    return isHeld && !wasHeld;
}

bool Input::GetKey(SDL_Keycode key)
{
	return std::find(_heldButtons.begin(), _heldButtons.end(), key) != _heldButtons.end();
}

bool Input::GetKeyUp(SDL_Keycode key)
{
    return std::any_of(_frameInput.begin(), _frameInput.end(),
                       [key](auto & input){return (input.type == SDL_KEYUP && key == input.keysym.sym);});
}
