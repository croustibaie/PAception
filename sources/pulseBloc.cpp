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

pulseBloc::pulseBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
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
    this->myKind=SOLID;
    this->compteur=0; // compteur d'absorptions ;
    loadMedia(&texture,gRenderer,"./textures/leopard.bmp");
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
        this->laser[i] = new laserBloc(gRenderer, "./textures/red.bmp", l, 50, 50, 1, 0);
    }
    this->nextLaser=0;



}

pulseBloc::~pulseBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool pulseBloc::collisionReaction(bloc *b)
{
    int temps_precedent = 0;
    int temps_actuel = 0;
        if (b->kill())

        {
            if (compteur < 4)
            {
                compteur = compteur + 1;

                std::cout<<compteur<<std::endl;

            }

            if (compteur == 4)
            {
                TimerPulse = SDL_GetTicks();
                compteur = compteur + 1;

                std::cout<<TimerPulse<<std::endl;
            }

            if (compteur > 4)
            {

                std::cout<<SDL_GetTicks()<<std::endl;
                if (SDL_GetTicks()-TimerPulse > 300)
                {
                    pulseBloc::shoot();
                    compteur = 0;
                }
                }
            }
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


            laser[nextLaser]->setPosition(x_init+radius*ctheta,y_init+radius*stheta);
            laser[nextLaser]->setDirection(ctheta,stheta);
            l->insertBlocs(laser[nextLaser],1);

            nextLaser=(nextLaser+1)%NB_LASERS2;

        }
    }
