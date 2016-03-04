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

laserBloc::laserBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y,int dx,int dy)
{
    this->dx=dx;
    this->dy=dy;
    this->l=l;
    if (*gRenderer==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    if((x<SCREEN_WIDTH-50)&&(y<SCREEN_HEIGHT-50)) {
        this->rect.x = x;
        this->rect.y = y;
    }
    else
    {
        this->rect.x=0; //TODO : see for throwing an exception
        this->rect.y=0;
    }
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
    int xmove = (int)(dx*float(elapsedTime));
    int ymove = (int)(dy*float(elapsedTime));
   tryMove(xmove,ymove);
    return true;
}

