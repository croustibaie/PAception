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
    int xMove;
    int yMove;
    static unsigned int nextBlocId;

    bool killOnTouch; //Does the bloc kill players?
//    virtual enum kind;

public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc ();
    bloc(const bloc& b);

    bloc (SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);

    ~bloc();

    virtual bool react(struct controllerState** state,unsigned int elapsedTime); //Bloc's reactions to given inputs, returns false if the bloc asked to be killed
    void draw();
    void move(int x , int y);
    virtual bool tryMove(int x, int y);//Returns false if the bloc asked to be killed, true otherwise.
    virtual void collisionReaction(bloc* b);
    virtual void wallCollision(SDL_Rect a); // Checks if the bloc collides a border, if yes, stop it in one direction and calls tryMove for the movement in another direction, do nothing otherwise
    void setSpeed(int speed);

    SDL_Rect getRect() const;
    int getSpeed() const;
    int getBlocId() const;
    SDL_Renderer* getRenderer() const;
    SDL_Texture* getTexture() const;
    bool kill();

};

#endif