cmake_minimum_required(VERSION 3.21)
project(2D_Game_Engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(Engine)
include_directories(Game)
include_directories(Game/Enteties)

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2/include)
set(SDL2_LIB_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_IMAGE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2_image/include)
set(SDL2_IMAGE_LIB_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2_image/lib/x64)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

set(SDL2_TTF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2_ttf/include)
set(SDL2_TTF_LIB_DIR ${CMAKE_SOURCE_DIR}/Libraries/SDL2_ttf/lib/x64)
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})


add_executable(2D_Game_Engine
        Engine/ArtemisEngine.cpp
        Engine/ArtemisEngine.h
        Engine/BoxCollider.cpp
        Engine/BoxCollider.h
        Engine/FontManager.cpp
        Engine/FontManager.h
        Engine/GameObject.cpp
        Engine/GameObject.h
        Engine/Input.cpp
        Engine/Input.h
        Engine/main.cpp
        Engine/MonoBehaviour.cpp
        Engine/MonoBehaviour.h
        Engine/Physics.cpp
        Engine/Physics.h
        Engine/RigidBody.cpp
        Engine/RigidBody.h
        Engine/Sprite.cpp
        Engine/Sprite.h
        Engine/SpriteManager.cpp
        Engine/SpriteManager.h
        Engine/Text.cpp
        Engine/Text.h
        Engine/TextureManager.cpp
        Engine/TextureManager.h
        Engine/Time.cpp
        Engine/Time.h
        Engine/Transform.cpp
        Engine/Transform.h
        Engine/Vector2.cpp
        Engine/Vector2.h
        Game/Enteties/EnemyShip.cpp
        Game/Enteties/EnemyShip.h
        Game/Enteties/Laser.cpp
        Game/Enteties/Laser.h
        Game/Enteties/PlayerShip.cpp
        Game/Enteties/PlayerShip.h
        Game/Enteties/Ship.cpp
        Game/Enteties/Ship.h
        Game/AssetLoader.cpp
        Game/GameManager.cpp
        Game/GameManager.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)
