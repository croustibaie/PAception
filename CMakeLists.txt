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
        )  #Set l'ensemble des sources, ici peu élégant

add_executable(PAception ${SOURCE_FILES}) #exécutable PAception génération par les fichiers sources

INCLUDE(FindPkgConfig) #Inclut le module Pkg qui permet de rechercher des librairies

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2) #pkg cherche la librairie sdl2, je ne comprends pas complétement la syntaxe

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ) #inclut les répertoires dont SDL2 a besoin, SDL2_INCLUDE_DIRS et probablement set grâce à pkg
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})  #Lors de la compilation du projet PROJECT_NAME, linker les libs SDL2
