//
// Created by Benoit on 10/03/16.
//

#include "../headers/voidBloc.h"
#include "../headers/playerBloc.h"
#include "../headers/level.h"

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

voidBloc::voidBloc(SDL_Renderer **gRenderer, level *l,int x,int y)
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

voidBloc::~voidBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool voidBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    return true;
}

bool voidBloc::collisionReaction(bloc *b)
{

     // radius of the small ball around the center of the cube
          // that will determine when the player cube vanishes

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

        // square of the euclidian distance
        dist_center = (void_center_x - b_center_x)*(void_center_x - b_center_x)
                      + (void_center_y - b_center_y)*(void_center_y - b_center_y) ;

        if (dist_center <= EPS)
        {
            this->l->deleteBloc(b->getBlocId(),b->getKind());
        }

    }

    return(true);

}
