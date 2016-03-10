//
// Created by gael on 09/03/16.
//

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
    this->myKind=STATIC;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;

}

pulseBloc::pulseBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y)
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
    this->myKind=STATIC;
    this->compteur=0; // compteur d'absorptions ;
    loadMedia(&texture,gRenderer,path);
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
        this->laser[i] = new laserBloc(gRenderer, "./black.bmp", l, 50, 50, 1, 0);
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
        if (b->getKind() == LASER)
            std::cout << "touché" << std::endl;
        {
            if (compteur < 12)
            {
                compteur = compteur + 1;
                std::cout << "laser absorbé" << std::endl;
            }
            else
            {
                Timer=SDL_GetTicks();
               // std::cout << "seuil dépassé" << std::endl;
                int elapsedTime=SDL_GetTicks();
                elapsedTime-= Timer;
                if (abs(elapsedTime)>3000)
                {
                    //shoot()
                }
            }
        }

    return true;
}


void pulseBloc::shoot( struct controllerState **state, int x_init, int y_init)
    {


        for (int i = 0; i < NB_LASERS2; i++)
        {;
            laser[nextLaser]->setPosition(x_init,y_init);
            (double) i;
            double ctheta = cos(i*45);
            double stheta = sqrt(1-ctheta*ctheta);

            laser[nextLaser]->setDirection(ctheta,stheta);
            l->insertBlocs(laser[nextLaser],1);



            nextLaser=(nextLaser+1)%NB_LASERS2;

        }



    }


