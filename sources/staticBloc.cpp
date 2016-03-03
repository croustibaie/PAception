//
// Created by croustibaie on 3/1/16.
//

#include "../headers/staticBloc.h"

staticBloc::staticBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
}

staticBloc::staticBloc(SDL_Renderer **gRenderer, const char *path, level *l)
{
    this->l=l;
    if (*gRenderer==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->rect.x=100;
    this->rect.y=100;
    this->rect.w=50;
    this->rect.h=50;
    texture=NULL;
    this->speed=0;
    this->gRenderer=*gRenderer;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
}

staticBloc::~staticBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool staticBloc::react(struct controllerState *state, unsigned int elapsedTime)
{
    return true;
}