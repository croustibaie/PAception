//
// Created by croustibaie on 12/14/15.
//

#include<SDL.h>
#include "../headers/sdlconfig.h"
#include "../headers/bloc.h"

int bloc::nextBlocId=0;

bloc::bloc ()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
}

bloc::bloc (SDL_Renderer** gRender,const char* path)
{
    if (*gRender==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->rect.x=0;
    this->rect.y=0;
    this->rect.w=50;
    this->rect.h=50;
    texture=NULL;
    this->speed=8;
    this->gRenderer=*gRender;
    loadMedia(&texture,gRender,path);
    this->blocId=nextBlocId;
    nextBlocId++;
}

bloc::~bloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void bloc::react(struct controllerState* state,unsigned int elapsedTime)
{
    int correctedSpeed= (int)(round((float)(speed)*(float)elapsedTime/20)); //We have to adapt the initial speed to the frame duration
    move(state->leftStickLeft ? -correctedSpeed : 0, state->leftStickDown ? -correctedSpeed : 0 );
    move(state->leftStickRight ? correctedSpeed : 0, state->leftStickUp ? correctedSpeed : 0 );
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

void bloc::setSpeed(int speed)
{
    this->speed=speed;
}

int bloc::getBlocId()
{
    return blocId;
}