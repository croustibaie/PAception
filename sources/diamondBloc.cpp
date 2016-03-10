//
// Created by Benoit on 10/03/16.
//

#include "../headers/diamondBloc.h"
#include "../headers/playerBloc.h"
#include "../headers/level.h"
#include "../headers/laserBloc.h"


diamondBloc::diamondBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->myKind = SOLID;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

diamondBloc::diamondBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y)
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
    this->myKind=NONSOLID;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    for (int i = 0; i < NB_LASERS; i++)
    {
        this->laser[i] = new laserBloc(gRenderer, "./textures/black.bmp", l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
}

diamondBloc::~diamondBloc()
{
}

bool diamondBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}

bool diamondBloc::collisionReaction(bloc *b)
{

    if(b->killOnTouch == true)
    {


    }

    return(true);

}

void diamondBloc::shoot(int x , int y)
{

    int xPos; int yPos;
    double xDir ; double yDir;

    if(y == 0)
    {
        if(x == 1)
        {
            xPos = this->rect.x + rect.w;
            yPos = this->rect.y + rect.h/2;
        }
        if(x == -1)
        {
            xPos = this->rect.x;
            yPos = this->rect.y + rect.h/2;
        }
    }
    if(x == 0)
    {
        if (y == 1) {
            xPos = this->rect.x + rect.w/2;
            yPos = this->rect.y;
        }
        if (y == -1) {
            xPos = this->rect.x + rect.w/2;
            yPos = this->rect.y + rect.h;
        }
    }

    xDir = x/sqrt(double(x*x+y*y)) ;
    yDir = y/sqrt(double(x*x+y*y)) ;

        laser[nextLaser]->setPosition(xPos,yPos);
        laser[nextLaser]->setDirection(xDir,yDir);

        l->insertBlocs(laser[nextLaser],1);

        nextLaser=(nextLaser+1)%NB_LASERS;
}
