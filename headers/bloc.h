//
// Created by croustibaie on 12/14/15.
//

#ifndef PA_BLOC_H
class level;
#include <iostream>
#include <SDL_surface.h>
#include "sdlconfig.h"



#define PA_BLOC_H


class bloc {

protected:
    SDL_Rect rect;// Bloc's hitbox
    SDL_Texture *texture;//Bloc's sprite
    SDL_Renderer* gRenderer;
    level* l;
    int speed;
    int blocId; //Bloc's unique ID, is it really useful?
    static unsigned int nextBlocId;


public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc ();
    bloc(const bloc& b);

    bloc (SDL_Renderer** gRenderer,const char* path,level* l);

    ~bloc();

    virtual void react(struct controllerState* state,unsigned int elapsedTime); //Bloc's reactions to given inputs
    void draw();
    void move(int x , int y);
    void tryMove(int x, int y);
    void collisionReaction(bloc* b);
    void setSpeed(int speed);

    SDL_Rect getRect() const;
    int getSpeed() const;
    int getBlocId() const;
    SDL_Renderer* getRenderer() const;
    SDL_Texture* getTexture() const;


};

#endif