//
// Created by Benoit on 10/03/16.
//

#include "../headers/voidBloc.h"
#include "../headers/playerBloc.h"
#include "../headers/level.h"
#include <math.h>

voidBloc::voidBloc()
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
}

voidBloc::voidBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, level *l,int x,int y)
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
    this->angle=0;
}

voidBloc::~voidBloc()
{
}

bool voidBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    angle=angle+(elapsedTime/5)-((int)(angle+(elapsedTime/5))/360)*360;
    return true;
}

bool voidBloc::collisionReaction(bloc *b)
{

    if(b->getKind()==PLAYER)
    {
        int void_center_x , void_center_y;
        int b_center_x , b_center_y ;
        int dist_center;
        // coordinates of the center of the void cube
        void_center_x = this->getRect().x + this->getRect().w/2 ;
        void_center_y = this->getRect().y + this->getRect().h/2 ;

        // coordinates of the center of the player cube
        b_center_x = b->getRect().x + b->getRect().w/2 ;
        b_center_y = b->getRect().y + b->getRect().h/2 ;

        // square of the euclidean distance
        dist_center = sqrt((void_center_x - b_center_x)*(void_center_x - b_center_x)
                      + (void_center_y - b_center_y)*(void_center_y - b_center_y)) ;

        if (dist_center <= KILLZONE)
        {
            this->l->deleteBloc(b->getBlocId(),b->getKind());
        }

    }
    return(true);
}

void voidBloc::draw()
{
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
    SDL_RenderCopyEx(gRenderer,texture, NULL, &this->rect,angle,NULL,SDL_FLIP_NONE );
}