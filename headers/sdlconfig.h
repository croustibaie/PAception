//
// Created by croustibaie on 1/10/16.
//

#ifndef PACEPTION_SDLCONFIG_H
#define PACEPTION_SDLCONFIG_H
#include <SDL.h>
#include <string>
#include<iostream>

/* This structure will be used to get the current state of an xBox controller*/
struct controllerState
{
    int leftStickHorizontal;
    int leftStickVertical;
    int rightStickHorizontal;
    int rightStickVertical;
    bool aButton;
    bool bButton;
    bool xButton;
    bool yButton;
    bool startButton;
};
//Starts up SDL and creates window
bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_GameController** gGameController);

//Loads media
bool loadMedia(SDL_Texture** gTexture,SDL_Renderer** gRenderer,char const* path);

//Frees media and shuts down SDL
void close(SDL_Renderer* gRenderer, SDL_Window* gWindow, SDL_GameController* gGameController );

#endif //PACEPTION_SDLCONFIG_H
