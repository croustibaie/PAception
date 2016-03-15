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

teleBloc::teleBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
{
    this->l=l;
    this->BOOLEAN == true ;
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


bool teleBloc::collisionReaction(bloc *b)
{

    if ((b->getKind()==PLAYER)&&(BOOLEAN ==true));
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
        dist_center = (void_center_x - b_center_x)*(void_center_x - b_center_x)
                      + (void_center_y - b_center_y)*(void_center_y - b_center_y) ;

        if (dist_center <= EPS2)
        {

            int Id = this->t->getBlocId(); // je veux l'id de l'autre teleBloc
            SDL_Rect rectTele= this->t->getRect(); // sa position...
            std::vector<bloc*> ignoreTele= this->t->getIgnoreBlocs(); //et tous les blocs qu'il doit ignorer !

            bloc* bloctest = l->collide(Id,rectTele,ignoreTele);
            if (bloctest == NULL)
            {

                b->setPosition(x_tele, y_tele);
                BOOLEAN = false;
                std::cout<< "je me suis téléporté"<<std::endl;

            }
            else
            {
                return(false);
            }

        }

    }

    return(true);

}



void teleBloc::setteleBloc(teleBloc* t2)
{
    this->x_tele = t2->getRect().x + t2->getRect().w / 2;
    this->y_tele = t2->getRect().y + t2->getRect().h / 2;

    //t1 téléporte vers t2 et réciproquement

    t2->x_tele = this->getRect().x + this->getRect().w / 2;
    t2->y_tele = this->getRect().y + this->getRect().h / 2;

    this->t=t2;
    t2->t=this;
}

bool teleBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
    return true;
}


/*
bool teleBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
    int tmp=0;
    std::map<bloc*,unsigned int>::iterator it;
    for (it=teleBloc.begin(); it!=teleBloc.end();it++)
    {
        if (SDL_GetTicks()-it->second>=TELETIME) // after a time of FREEZETIME ms sets the speed of a frozen bloc to INITIALSPEED
        {

            (it->first)->setSpeed(INITIALSPEED);
            blocarray[tmp]=it->first;
            tmp++;
        }
    }
    for (int i=0; i<tmp;i++)
    {
        frozenbloc.erase(blocarray[i]);
    }

    return true;
}
*/

