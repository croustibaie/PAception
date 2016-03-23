//
// Created by Benoit on 10/03/16.
//

#include "../headers/diamondBloc.h"
#include "../headers/level.h"
#include <math.h>

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
    this->laser_counter = 1;
}

diamondBloc::diamondBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture,SDL_Texture* laserTexture, level *l,int x,int y)
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
    this->rect.w=BLOCSIZE;
    this->rect.h=BLOCSIZE;
    texture=NULL;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->gRenderer=*gRenderer;
    this->myKind=SOLID;
    this->reflect=false;
    this->shield=false;
    this->texture=itexture;
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->isBumped=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    for (int i = 0; i < NB_LASERS3; i++)
    {
        this->laser[i] = new laserBloc(gRenderer,laserTexture, l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
    this->laser_counter = 1; // defines the vertex of the cube from which the refracted laser
                             // will be issued
}

diamondBloc::~diamondBloc()
{
    for (int i=0; i< NB_LASERS3;i++)
    {
        delete(this->laser[i]);
    }
}

bool diamondBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}

bool diamondBloc::collisionReaction(bloc *b)
{

    if(b->kill() == true)
    {
        if (laser_counter > 4)
        {
            std::cout << " error : wrong argument for laser counter" << std::endl;
        }
        switch (laser_counter)
        {
            case 1 :
                shoot(0);
                laser_counter +=1;
                break;
            case 2 :
                shoot(-M_PI/2);
                laser_counter +=1;
                break;
            case 3 :
                shoot(M_PI);
                laser_counter +=1;
                break;
            case 4 :
                shoot(M_PI/2);
                laser_counter = 1;
                break;
        }

    }

    return(true);
}

void diamondBloc::shoot(double tht)
{

    double xPos = 0;
    double yPos = 0;
    double xDir = cos(tht);
    double yDir = sin(tht);

    // right side and vertexes

    if(fabs(tht) < M_PI/4 - EPS_THT) // right side of the cube
    {
        xPos = this->rect.x + rect.w + EPS_SEC;
        yPos = this->rect.y + rect.h / 2.;
    }

    if(fabs(tht) >= M_PI/4 - EPS_THT)  // right corners
    {
        if(fabs(tht) <= M_PI/4 + EPS_THT && tht >0) // up right corner
        {
            xPos = this->rect.x + rect.w + EPS_SEC;
            yPos = this->rect.y - EPS_SEC;
        }

        if(fabs(tht) <= M_PI/4 + EPS_THT && tht <0) // down right corner
        {
            xPos = this->rect.x + rect.w + EPS_SEC;
            yPos = this->rect.y + rect.h + EPS_SEC;
        }
    }

    // left side and vertexes

    if(fabs(tht) > 3*M_PI/4 + EPS_THT) // left side of the cube
    {
        xPos = this->rect.x - EPS_SEC;
        yPos = this->rect.y + rect.h / 2.;
    }

    if(fabs(tht) <= 3*M_PI/4 + EPS_THT)
    {
        if(fabs(tht) > 3*M_PI/4 - EPS_THT && tht >0) // up left corner
        {
            xPos = this->rect.x - EPS_SEC;
            yPos = this->rect.y - EPS_SEC;
        }

        if(fabs(tht) > 3*M_PI/4 - EPS_THT && tht <0) // down left corner
        {
            xPos = this->rect.x - EPS_SEC;
            yPos = this->rect.y + rect.h + EPS_SEC;
        }
    }

    // down side and up side


    if (tht > M_PI/4 + EPS_THT && tht < 3*M_PI/4) // down side of the cube
    {
        xPos = this->rect.x + rect.w / 2.;
        yPos = this->rect.y + rect.h + EPS_SEC;
    }

    if (tht < -M_PI/4 - EPS_THT && tht > -3*M_PI/4 + EPS_THT) // upper side of the cube
    {
        xPos = this->rect.x + rect.w/2.;
        yPos = this->rect.y - EPS_SEC;
    }

        laser[nextLaser]->setPosition((int)xPos,(int)yPos);
        laser[nextLaser]->setDirection((float)xDir,(float)yDir);

        l->insertBloc(laser[nextLaser]);

        nextLaser=(nextLaser+1)%NB_LASERS3;
}
