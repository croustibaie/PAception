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
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    this->blocId=nextBlocId;
    nextBlocId++;
}

bloc::bloc(const bloc& b)
{
    this->gRenderer=b.getRenderer();
    loadMedia(&texture,&gRenderer,"/home/croustibaie/Documents/PAception/red.bmp");
    // this->texture=b.getTexture();
    this->rect=b.getRect();
    this->speed=b.getSpeed();
    this->blocId=b.getBlocId();
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
    move((int)(correctedSpeed*(float)(state->leftStickHorizontal)/32000),(int)(correctedSpeed*(float)(state->leftStickVertical)/32000) );
}

void bloc::draw()
{
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
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

int bloc::getBlocId() const
{
    return blocId;
}

 SDL_Renderer* bloc::getRenderer() const
{
    return gRenderer;
}

SDL_Texture* bloc::getTexture() const
{
    return texture;
}

SDL_Rect bloc::getRect() const
{
    return rect;
}

int bloc::getSpeed() const
{
    return speed;
}