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
    this->dx=(float)dx/sqrt((double)(dx*dx+dy*dy));
    this->dy=(float)dy/sqrt((double)(dx*dx+dy*dy));
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
    this->speed=8;
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


bool laserBloc::tryMove(int x, int y)
{
    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    int xmove=x;
    int ymove=y;
    bloc* intersectedBloc = this->l->collide(this->blocId,a);
    if (intersectedBloc!= nullptr) //If there is a collision
    {

        this->collisionReaction(intersectedBloc);
        intersectedBloc->collisionReaction(this);
        return true;
    }
    else //Here we check that we're not trying to go out of the window
    {

        if (a.x+a.w>=SCREEN_WIDTH) //TODO : think about a strict or large inequality
        {
            xmove=xmove-(a.x+a.w-SCREEN_WIDTH);
            this->dx=- this->dx;
        }
        if (a.x<0)
        {
            this->dx=- this->dx;
            xmove=xmove-a.x;
        }
        if (a.y+a.h>SCREEN_HEIGHT) //TODO: Same as previously
        {
            this->dy=- this->dy;
            ymove=ymove-(a.y+a.h-SCREEN_HEIGHT);

        }
        if (a.y<0)
        {
            this->dy=- this->dy;
            ymove=ymove-a.y;
        }
        move(xmove,ymove);
    }
    return true;
}


bool laserBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    int xmove = (int)(speed*dx*float(elapsedTime)/20);
    int ymove = (int)(speed*dy*float(elapsedTime)/20);
    tryMove(xmove,ymove);
    return true;
}

