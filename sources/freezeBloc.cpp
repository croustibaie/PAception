//
// Created by emilien on 09/03/16.
//

#include "../headers/freezeBloc.h"
#include "../headers/playerBloc.h"
freezeBloc::freezeBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->myKind=STATIC;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

freezeBloc::freezeBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y)
{
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
    this->myKind=FREEZE;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

freezeBloc::~freezeBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool freezeBloc::collisionReaction(bloc *b)
{
    if(b->getKind()==PLAYER)
    {
        b->setSpeed(4); // set the speed of a player bloc to 4
    }
    frozenbloc.insert(std::pair<bloc*,unsigned int>(b,SDL_GetTicks()));
}

bool freezeBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
    std::map<bloc*,unsigned int>::iterator it;
    for (it=frozenbloc.begin(); it!=frozenbloc.end();it++)
    {
        if (SDL_GetTicks()-it->second>=FREEZETIME) // after a time of FREEZETIME ms sets the speed of a frozen bloc to INITIALSPEED
        {
            std::cout<<"reseting speed"<<std::endl;
            (it->first)->setSpeed(INITIALSPEED);
            frozenbloc.erase(it->first);
        }
    }

    return true;
}