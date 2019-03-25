cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -lSDL2 -lSDL2_image")

project(HelloSDL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(HelloSDL src/main.cpp src/Game.h src/Game.cpp src/TextureManager.h src/TextureManager.cpp src/Player.cpp src/Player.h src/GameObject.h src/Enemy.cpp src/Enemy.h src/LoaderParams.h src/SDLGameObject.cpp src/SDLGameObject.h src/Vector2D.h src/InputHandler.cpp src/InputHandler.h)
target_link_libraries(HelloSDL ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )