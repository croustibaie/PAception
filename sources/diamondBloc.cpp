//
// Created by Benoit on 10/03/16.
//

#include "../headers/diamondBloc.h"
#include "../headers/level.h"

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

diamondBloc::diamondBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
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
    loadMedia(&texture,gRenderer,"./textures/carre2.png");
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    for (int i = 0; i < NB_LASERS3; i++)
    {
        this->laser[i] = new laserBloc(gRenderer, "./textures/black.bmp", l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
    this->laser_counter = 1; // defines the vertex of the cube from which the refracted laser
                             // will be issued
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

    if(b->kill() == true)
    {
        if (laser_counter > 4)
        {
            std::cout << " error : wrong argument for laser counter" << std::endl;
        }
        switch (laser_counter)
        {
            case 1 :
                shoot(1,0);
                laser_counter +=1;
                break;
            case 2 :
                shoot(0,-1);
                laser_counter +=1;
                break;
            case 3 :
                shoot(-1,0);
                laser_counter +=1;
                break;
            case 4 :
                shoot(0,1);
                laser_counter = 1;
                break;
        }



    }

    return(true);
}

void diamondBloc::shoot(int x , int y)
{

    double xPos=0; double yPos=0;
    double xDir = double(x);
    double yDir = double(y);

    if(y == 0)
    {
        if(x == 1)
        {
            xPos = this->rect.x + rect.w + EPS_SEC;
            yPos = this->rect.y + rect.h/2.;
        }
        if(x == -1)
        {
            xPos = this->rect.x - EPS_SEC;
            yPos = this->rect.y + rect.h/2.;
        }
    }
    else if(x == 0)
    {
        if (y == -1) {
            xPos = this->rect.x + rect.w/2.;
            yPos = this->rect.y - EPS_SEC;
        }
        if (y == 1) {
            xPos = this->rect.x + rect.w/2.;
            yPos = this->rect.y + rect.h + EPS_SEC;
        }
    }
    else
        std::cout << "fire direction can only be expressed using 0 "
                             "and 1 values for x and y" << std::endl;

        laser[nextLaser]->setPosition((int)xPos,(int)yPos);
        laser[nextLaser]->setDirection((float)xDir,(float)yDir);

        l->insertBlocs(laser[nextLaser],1);

        nextLaser=(nextLaser+1)%NB_LASERS3;
}
