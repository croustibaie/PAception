//
// Created by remi on 14/03/16.
//


#include "../headers/mirrorBloc.h"

mirrorBloc::mirrorBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->myKind=SOLID;
    this->reflect=true;
    this->shield=false;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

mirrorBloc::mirrorBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
{
    this->isBumped=false;
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
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->gRenderer=*gRenderer;
    this->myKind=SOLID;
    this->reflect=true;
    loadMedia(&texture,gRenderer,"./textures/black.bmp");
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

mirrorBloc::~mirrorBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool mirrorBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}