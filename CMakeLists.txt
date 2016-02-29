cmake_minimum_required(VERSION 3.0)
project(PAception)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        sources/bloc.cpp
        headers/bloc.h
        sources/main.cpp
        headers/sdlconfig.h
        sources/sdlconfig.cpp
        headers/level.h
        sources/level.cpp
        headers/userInterface.h
        sources/userInterface.cpp
        )

add_executable(PAception ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
