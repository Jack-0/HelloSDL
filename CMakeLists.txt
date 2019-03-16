cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -lSDL2 -lSDL2_image")

project(HelloSDL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(HelloSDL main.cpp Game.h Game.cpp TextureManager.h)
target_link_libraries(HelloSDL ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )



