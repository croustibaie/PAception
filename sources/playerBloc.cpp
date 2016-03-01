//
// Created by croustibaie on 3/1/16.
//

#include "../headers/playerBloc.h"

playerBloc::playerBloc()
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

playerBloc::playerBloc(SDL_Renderer **gRenderer, const char *path, level *l)
{
    this->l=l;
    if (*gRenderer==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->rect.x=0;
    this->rect.y=0;
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
    this->blocId=nextBlocId;
    nextBlocId++;
}

playerBloc::~playerBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void playerBloc::react(struct controllerState *state, unsigned int elapsedTime)
{
    int correctedSpeed= (int)(round((float)(speed)*(float)elapsedTime/20)); //We have to adapt the initial speed to the frame duration
    tryMove((int)(correctedSpeed*(float)(state->leftStickHorizontal)/32000),(int)(correctedSpeed*(float)(state->leftStickVertical)/32000) );
}