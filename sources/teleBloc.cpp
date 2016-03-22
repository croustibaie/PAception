//
// Created by gael on 14/03/16.
//

#include <X11/Xlib.h>
#include "../headers/voidBloc.h"
#include "../headers/playerBloc.h"
#include "../headers/level.h"
#include "../headers/teleBloc.h"

teleBloc::teleBloc()
{
    this->rect.x=BLOCSIZE;
    this->rect.y =BLOCSIZE;
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

teleBloc::teleBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
{
    this->l=l;
    this->isBumped=false;
    this->active = true ;
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
    loadMedia(&texture,gRenderer,"./textures/black.bmp");
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

teleBloc::~teleBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void teleBloc::setSibling(teleBloc *t)
{
    this->t=t;
}

bool teleBloc::collisionReaction(bloc *b)
{

    if ((this->active)&&(b->getKind()==PLAYER))
    {
        int void_center_x, void_center_y;
        int b_center_x, b_center_y;
        int dist_center;
        // coordinates of the center of the void cube
        void_center_x = this->getRect().x + this->getRect().w / 2;
        void_center_y = this->getRect().y + this->getRect().h / 2;

        // coordinates of the center of the player cube
        b_center_x = b->getRect().x + b->getRect().w / 2;
        b_center_y = b->getRect().y + b->getRect().h / 2;

        // square of the euclidean distance
        dist_center = (void_center_x - b_center_x) * (void_center_x - b_center_x)
                      + (void_center_y - b_center_y) * (void_center_y - b_center_y);

        if (dist_center <= EPS2)
        {
            int Id = this->t->getBlocId(); // je veux l'id de l'autre teleBloc
            SDL_Rect rectTele = this->t->getRect(); // sa position...
            std::vector<bloc *> ignoreTele = this->t->getIgnoredBlocs(); //et tous les blocs qu'il doit ignorer !

            bloc *bloctest = l->collide(Id, rectTele, ignoreTele);

            if (bloctest == NULL)
            {

                b->setPosition(this->t->getRect().x+this->t->getRect().w/2, this->t->getRect().y+this->t->getRect().h/2);
                this->t->setBool(false);

                this->t->timerTele=SDL_GetTicks();
            }
            else{
                std::cout<<bloctest->getBlocId()<<std::endl;
            }

        }
        else
        {

        }
        return (true);
    }
}



void teleBloc::setteleBloc(teleBloc* t2)
{
    /*

    this->x_tele = t2->getRect().x + t2->getRect().w / 2;
    this->y_tele = t2->getRect().y + t2->getRect().h / 2;

    //t1 téléporte vers t2 et réciproquement

    t2->x_tele = this->getRect().x + this->getRect().w / 2;
    t2->y_tele = this->getRect().y + this->getRect().h / 2;

    */
    this->t=t2;
    t2->setSibling(this);
}

/*
bool teleBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
    return true;
}


*/

bool teleBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
        if (SDL_GetTicks()-timerTele > 500)
        {
            this->active=true;
        }


    return true;
}


void teleBloc::setBool(bool b)
{
       this->active=b;
}