//
// Created by croustibaie on 12/14/15.
//

#include<SDL.h>
#include "../headers/sdlconfig.h"
#include "../headers/bloc.h"

bloc::bloc ()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    texture=NULL;
    gRenderer=NULL;
}

bloc::bloc (SDL_Renderer** gRender,const char* path)
{
this->rect.x=0;
this->rect.y=0;
this->rect.w=50;
this->rect.h=50;
texture=NULL;
this->gRenderer=*gRender;
loadMedia(&texture,gRender,path);
}

bloc::~bloc() {};

void bloc::react(struct controllerState* state,unsigned int elapsedTime)
{
    printf("%d %u\n",elapsedTime, elapsedTime/2);
    move(state->leftStickLeft ? -4 : 0, state->leftStickDown ? -4 : 0 );
    move(state->leftStickRight ? 4 : 0, state->leftStickUp ? 4 : 0 );
}

void bloc::draw()
{
    SDL_RenderCopy(gRenderer,texture, NULL, &rect );
}
void bloc::move(int x , int y)
{
    this->rect.x+=x;
    this->rect.y+=y;
}
