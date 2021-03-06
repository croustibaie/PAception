//
// Created by croustibaie on 1/10/16.
//

#ifndef PACEPTION_SDLCONFIG_H
#define PACEPTION_SDLCONFIG_H
#include <SDL.h>

#include <string>
#include<iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int LASER_WIDTH = 10;
const int LASER_HEIGHT = 10;
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
    bool RT;
    bool LT;
    bool startButton;
};

enum kind {
    PLAYER,
    SOLID,
    NONSOLID,
    MIRROR,
};
//Starts up SDL and creates window
bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_GameController** gGameController);

//Loads media
bool loadMedia(SDL_Texture** gTexture,SDL_Renderer** gRenderer,char const* path);

//Frees media and shuts down SDL
void close(SDL_Renderer* gRenderer, SDL_Window* gWindow, SDL_GameController** gGameController );



#endif //PACEPTION_SDLCONFIG_H
