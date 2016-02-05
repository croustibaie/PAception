//
// Created by croustibaie on 12/14/15.
//

#ifndef PA_BLOC_H
#include <iostream>
#include <SDL_surface.h>
#include "sdlconfig.h"
#define PA_BLOC_H


class bloc {

private:
    SDL_Rect rect;
    SDL_Texture *texture;
    int speed;
    SDL_Renderer* gRenderer;
    int blocId;
    static int nextBlocId;


public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc ();

    bloc (SDL_Renderer** gRenderer,const char* path);

    ~bloc();

    void react(struct controllerState* state,unsigned int elapsedTime);
    void draw();
    void move(int x , int y);
    void setSpeed(int speed);
    int getBlocId();


};

#endif