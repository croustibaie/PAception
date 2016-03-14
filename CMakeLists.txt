cmake_minimum_required(VERSION 3.0) #Indique la version de cmake à utiliser
project(PAception) #indique le nom du projet réalisé par le cmake, utile quand on imbrique des Cmake

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #Commande de set, CMAKE_CXX_FLAGS = CMAKE_CXX_FLAGS + "-std=c++11"

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
        headers/playerBloc.h
        sources/playerBloc.cpp
        headers/staticBloc.h
        sources/staticBloc.cpp
        headers/laserBloc.h
        sources/laserBloc.cpp
        headers/pulseBloc.h
        sources/pulseBloc.cpp
        headers/sound.h
        sources/sound.cpp
        headers/freezeBloc.h
        sources/freezeBloc.cpp
        sources/voidBloc.cpp
        headers/voidBloc.h
        sources/diamondBloc.cpp
        headers/diamondBloc.h
        headers/bumpBloc.h
        sources/bumpBloc.cpp
        headers/levelCreator.h
        sources/levelCreator.cpp) #Set l'ensemble des sources, ici peu élégant

add_executable(PAception ${SOURCE_FILES}) #exécutable PAception génération par les fichiers sources

INCLUDE(FindPkgConfig) #Inclut le module Pkg qui permet de rechercher des librairies

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2) #pkg cherche la librairie sdl2, je ne comprends pas complétement la syntaxe
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}  ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS}) #inclut les répertoires dont SDL2 a besoin, SDL2_INCLUDE_DIRS et probablement set grâce à pkg
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES})  #Lors de la compilation du projet PROJECT_NAME, linker les libs SDL2
