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
    SDL_Rect rect;// Bloc's hitbox
    SDL_Texture *texture;//Bloc's sprite
    int speed;
    SDL_Renderer* gRenderer;
    int blocId; //Bloc's unique ID, is it really usefull?
    static int nextBlocId;


public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc ();
    bloc(const bloc& b);

    bloc (SDL_Renderer** gRenderer,const char* path);

    ~bloc();

    void react(struct controllerState* state,unsigned int elapsedTime); //Bloc's reactions to given inputs
    void draw();
    void move(int x , int y);
    void setSpeed(int speed);

    SDL_Rect getRect() const;
    int getSpeed() const;
    int getBlocId() const;
    SDL_Renderer* getRenderer() const;
    SDL_Texture* getTexture() const;


};

#endif