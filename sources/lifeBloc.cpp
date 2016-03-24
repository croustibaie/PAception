//
// Created by emilien on 24/03/16.
//

#include "../headers/lifeBloc.h"
#include "../headers/level.h"
#include <math.h>

lifeBloc::lifeBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->myKind=NONSOLID;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->lifetimer=-HPTIME;
}

lifeBloc::lifeBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, level *l,int x,int y)
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
    this->rect.w=BLOCSIZE;
    this->rect.h=BLOCSIZE;
    texture=NULL;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->gRenderer=*gRenderer;
    this->myKind=NONSOLID;
    this->reflect=false;
    this->shield=false;
    this->texture=itexture;
    if (this->texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->lifetimer=-HPTIME;
}

lifeBloc::~lifeBloc()
{
}

bool lifeBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}

bool lifeBloc::collisionReaction(bloc *b)
{
    if (SDL_GetTicks()-lifetimer> HPTIME)
    {
        b->addHp(HPSTOCK);
        lifetimer=SDL_GetTicks();
    }

    return(true);
}

