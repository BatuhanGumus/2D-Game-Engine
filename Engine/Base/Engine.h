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
        Engine(const char* title, int xPos, int yPos, int widthPX, int heightPX, bool fullScreen);
        ~Engine();

        void UpdateGameObjectList();
        void HandleEvents();
        void Update();
        void Render();
        void Clean();

        bool IsGameRunning();

        void Awake();
        void LoadAssets();

        static void GameObjectCreated(GameObject* gameObject);
        static void Destroy(GameObject* gameObject);

        static SDL_Renderer* renderer;
        SDL_Event event;

        static std::vector<GameObject*> gameObjects;
        static std::queue<GameObject*> gameObjectsToAdd;
        static std::queue<GameObject*> gameObjectsToRemove;

        static std::vector<Text*> textsToRender;

        static int pixW;
        static int pixH;
        static double pixPerWorld;

        Physics* physicsEngine;

    private:
        bool isRunning;
        SDL_Window* window;
    };

}


