//
// Created by gael on 09/03/16.
//

#include <unistd.h>
#include "../headers/pulseBloc.h"
#include "../headers/level.h"


pulseBloc::pulseBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->myKind=SOLID;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;

}

pulseBloc::pulseBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture,SDL_Texture* laserTexture, level *l,int x,int y)
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
    this->myKind=SOLID;
    this->reflect=false;
    this->shield=false;
    this->compteur=0; // compteur d'absorptions ;
    this->texture=itexture;
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    for (int i = 0; i < NB_LASERS2; i++)
    {
        this->laser[i] =  laserBloc(gRenderer,laserTexture, l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
}

pulseBloc::~pulseBloc()
{
}

bool pulseBloc::collisionReaction(bloc *b) {
       if (b->kill())
    {

        compteur = compteur + 1;

        if (compteur == 4)
        {
            TimerPulse = SDL_GetTicks();
            compteur = compteur+1;

        }

    }
    return true;
}

void pulseBloc::shoot()
    {
        for (int i = 0; i < NB_LASERS2; i++)
        {
            float x_init = this->rect.x+(this->rect.w)/2;
            float y_init = this->rect.y+(this->rect.h)/2;
            float radius = sqrt(((this->rect.w)/2)*((this->rect.w)/2)+((this->rect.h)/2)*((this->rect.h)/2));
            radius = 2*radius+1;

            (double) i;
            double ctheta = cos(M_PI/4*i);
            double stheta = sin(M_PI/4*i);


            laser[nextLaser].setPosition(x_init+radius*ctheta,y_init+radius*stheta);
            laser[nextLaser].setDirection(ctheta,stheta);
            l->insertBloc(&laser[nextLaser]);

            nextLaser=(nextLaser+1)%NB_LASERS2;

        }
    }


bool pulseBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    if (compteur > 4)
        {

            if (SDL_GetTicks()-TimerPulse > 3000)
            {
                pulseBloc::shoot();
                compteur = 0;
            }
        }

    return true;
}
