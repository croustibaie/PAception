//
// Created by croustibaie on 1/10/16.
//

#ifndef PACEPTION_SDLCONFIG_H
#define PACEPTION_SDLCONFIG_H
#include <SDL.h>
#include <string>
#include<iostream>

//Starts up SDL and creates window
bool init(SDL_Window** gWindow, SDL_Surface** gScreenSurface, SDL_GameController** gGameController);

//Loads media
bool loadMedia(SDL_Surface** gSurface, char const* path);

//Frees media and shuts down SDL
void close(SDL_Surface* gSurface, SDL_Window* gWindow, SDL_GameController* gGameController );

#endif //PACEPTION_SDLCONFIG_H
