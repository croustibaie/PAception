//
// Created by croustibaie on 3/1/16.
//

#include "../headers/playerBloc.h"
#include "../headers/level.h"

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

playerBloc::playerBloc(SDL_Renderer **gRenderer, const char *path, level *l, int playerID)
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
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->playerID = playerID;
}

playerBloc::~playerBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void playerBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    int correctedSpeed= (int)(round((float)(speed)*(float)elapsedTime/20)); //We have to adapt the initial speed to the frame duration
    tryMove((int)(correctedSpeed*(float)(state[playerID]->leftStickHorizontal)/32000),(int)(correctedSpeed*(float)(state[playerID]->leftStickVertical)/32000) );
}

void playerBloc::tryMove(int x, int y)
{

    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    int xmove=x;
    int ymove=y;
    bloc* intersectedBloc = this->l->collide(this->blocId,a);
    if (intersectedBloc!= nullptr) //If there is a collision
    {
        if (intersectedBloc->kill())
        {
            std::cout<<"got killed"<<std::endl;
            this->l->deleteBloc(this->blocId);
        }
        this->move(0,0); //TODO: bloc's collision reaction should be there
    }
    else //Here we check that we're not trying to go out of the window
    {
        if (a.x+a.w>SCREEN_WIDTH)
        {
            xmove=SCREEN_WIDTH-(this->getRect().x+this->getRect().w);
        }
        if (a.x<0)
        {
            xmove=- (this->getRect().x);
        }
        if (a.y+a.h>SCREEN_HEIGHT)
        {
            ymove=SCREEN_HEIGHT-(this->getRect().y + this->getRect().h);
        }
        if (a.y<0)
        {
            ymove=- (this->getRect().y);
        }
        move(xmove,ymove);
    }
}