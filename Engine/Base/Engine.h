#pragma once
#include "SDL.h"
#include "MonoBehaviour.h"
#include <vector>
#include "Physics.h"
#include "Text.h"
#include <queue>

namespace ArtemisEngine
{
    class Engine
    {
    public:
        Engine(const char* title, int xPos, int yPos, int widthPX, int heightPX, int pixelPerUnit, bool fullScreen);
        ~Engine();

        void UpdateGameObjectList();
        void HandleEvents();
        void Update();
        void Render();
        void Clean();

        [[nodiscard]] bool IsGameRunning() const;

        void Awake();
        void LoadAssets();

        static void GameObjectCreated(GameObject* gameObject);
        static void Destroy(GameObject* gameObject);

        static SDL_Renderer* renderer;
        SDL_Event event;

        static std::vector<Text*> textsToRender;

        static int pixW;
        static int pixH;
        static double pixelPerUnit;

    private:
        bool _isRunning;
        SDL_Window* _window;

        static std::vector<GameObject*> _gameObjects;
        static std::queue<GameObject*> _gameObjectsToAdd;
        static std::queue<GameObject*> _gameObjectsToRemove;
    };

}


