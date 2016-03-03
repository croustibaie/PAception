//
// Created by croustibaie on 3/3/16.
//

#include "../headers/laserBloc.h"

laserBloc::laserBloc()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    texture=NULL;
    gRenderer=NULL;
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
}

laserBloc::laserBloc(SDL_Renderer **gRenderer, const char *path, level *l)
{
    this->l=l;
    if (*gRenderer==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->rect.x=100;
    this->rect.y=150;
    this->rect.w=50;
    this->rect.h=50;
    texture=NULL;
    this->speed=16;
    this->gRenderer=*gRenderer;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
}

laserBloc::~laserBloc()
{
}

bool laserBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}