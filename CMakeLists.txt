cmake_minimum_required(VERSION 3.7)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -lSDL2")

project(HelloSDL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(HelloSDL main.cpp Game.h Game.cpp)
target_link_libraries(HelloSDL ${SDL2_LIBRARIES})

