#pragma once
#include "SDL.h"
#include <vector>

 namespace ArtemisEngine
 {
     class Input
     {
     public:
         static bool GetKeyDown(SDL_Keycode key);
         static bool GetKeyUp(SDL_Keycode key);
         static bool GetKey(SDL_Keycode key);

         static void PassInFrameInput(SDL_KeyboardEvent keyEvent);
         static void ClearInputBuffer();

     private:
         static std::vector<SDL_Keycode> _heldButtons;
         static std::vector<SDL_Keycode> _lastFrame;
         static std::vector<SDL_KeyboardEvent> _frameInput;
     };
 }



