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
    SDL_Surface *texture;


public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc ()
    {
        this->rect.x=0;
        this->rect.y =0;
        this->rect.w=10;
        this->rect.h=10;
        texture=NULL;
    }

    bloc (char* path)
    {
        this->rect.x=0;
        this->rect.y=0;
        this->rect.w=50;
        this->rect.h=50;
        texture=NULL;
        loadMedia(&texture,path);
    }

    ~bloc() {};

    void draw(SDL_Surface* gScreenSurface)
    {
        SDL_BlitScaled( texture, NULL, gScreenSurface, &rect );
    }
    void move(int x , int y)
    {
        this->rect.x+=x;
        this->rect.y+=y;
    }


};

#endif