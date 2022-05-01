cmake_minimum_required(VERSION 3.21)
project(2D_Game_Engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(Engine)
include_directories(Engine/Base)
include_directories(Engine/Components)
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
        Engine/main.cpp
        Engine/Base/Engine.cpp
        Engine/Base/Engine.h
        Engine/Base/FontManager.cpp
        Engine/Base/FontManager.h
        Engine/Base/GameObject.cpp
        Engine/Base/GameObject.h
        Engine/Base/Input.cpp
        Engine/Base/Input.h
        Engine/Base/MonoBehaviour.cpp
        Engine/Base/MonoBehaviour.h
        Engine/Base/Physics.cpp
        Engine/Base/Physics.h
        Engine/Base/Sprite.cpp
        Engine/Base/Sprite.h
        Engine/Base/Text.cpp
        Engine/Base/Text.h
        Engine/Base/Time.cpp
        Engine/Base/Time.h
        Engine/Base/Transform.cpp
        Engine/Base/Transform.h
        Engine/Base/Vector2.cpp
        Engine/Base/Vector2.h
        Engine/Components/BoxCollider.cpp
        Engine/Components/BoxCollider.h
        Engine/Components/RigidBody.cpp
        Engine/Components/RigidBody.h
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
        Game/GameManager.h
        Engine/Base/Component.cpp
        Engine/Base/Component.h
        Engine/Components/SpriteRenderer.cpp
        Engine/Components/SpriteRenderer.h
        Engine/Base/Color.cpp
        Engine/Base/Color.h 
        Engine/Base/Debug.cpp
        Engine/Base/Debug.h
        Engine/Base/Event.h
        Engine/Base/Event.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/libraries/SDL2/lib/x64"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Libraries/SDL2_image/lib/x64"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Libraries/SDL2_ttf/lib/x64"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)