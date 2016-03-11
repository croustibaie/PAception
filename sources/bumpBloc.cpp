//
// Created by emilien on 11/03/16.
//




#include "../headers/bumpBloc.h"
#include "../headers/level.h"
bumpBloc::bumpBloc()
{
    this->rect.x=50;
    this->rect.y =50;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=0;
    this->xMove=0;
    this->yMove=0;
    this->dx=0;
    this->dy=0;
    this->myKind=SOLID;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->bumpededge=NONE;
}

bumpBloc::bumpBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y,int dx,int dy)
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
    this->dx=(float)(dx/sqrt((double)(dx*dx+dy*dy)));
    this->dy=(float)(dy/sqrt((double)(dx*dx+dy*dy)));
    this->gRenderer=*gRenderer;
    this->myKind=SOLID;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->bumpededge=NONE;
}

bumpBloc::~bumpBloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

bool bumpBloc::collisionReaction(bloc *b)
{

    bool isAlive;
    if (b->getKind()!=MIRROR)
    {
        this->l->deleteBloc(this->blocId,this->getKind());
        isAlive=false;
        return isAlive;
    }
    float tx, ty;
    tx = 0;
    ty = 0;
    int deltaX, deltaY;
    deltaX = 0;
    deltaY = 0;
    if (xMove > 0) // intention to move to the right
    {
        deltaX = b->getRect().x - (this->getRect().x + this->getRect().w) - 1;
    }
    if (xMove < 0) // intention to move to the left
    {
        deltaX = this->getRect().x - (b->getRect().x + b->getRect().w) - 1;
    }
    if (yMove > 0 ) // intention to move upward
    {
        deltaY = b->getRect().y - (this->getRect().y + this->getRect().h) - 1;
    }
    if (yMove < 0) // intention to move downward
    {
        deltaY = this->getRect().y - (b->getRect().y + b->getRect().h) - 1;
    }
    if ((xMove == 0) ) // no horizontal move tried
    {
        yMove = yMove == 0 ? 0 : -yMove / (abs(yMove)) * (deltaY);
        dy=-dy;
        isAlive=tryMove(0, yMove);
        return isAlive;
    }
    if ((yMove == 0) ) //no vertical move tried
    {
        xMove = xMove == 0 ? 0 : -xMove / (abs(xMove)) * (deltaX);
        dx=-dx;
        isAlive=tryMove(xMove, 0);
        return isAlive;
    }
    if (deltaX<0)
    {
        yMove= yMove == 0 ? 0: -yMove/(abs(yMove))*(deltaY);
        dy=-dy;
        isAlive=tryMove(xMove, yMove );
        return isAlive;
    }
    if (deltaY<0)
    {
        xMove= xMove == 0 ? 0 : -xMove/(abs(xMove))*(deltaX);
        dx=-dx;
        isAlive=tryMove(xMove ,yMove);
        return isAlive;
    }
    tx = deltaX / xMove;
    ty = deltaY / yMove;
    if (tx < ty)
    {
        xMove = xMove / (abs(xMove)) * (deltaX);
        isAlive=tryMove(xMove, yMove);
        return isAlive;
    }
    else
    {
        yMove = yMove / (abs(yMove)) * (deltaY);
        isAlive=tryMove(xMove, yMove);
        return isAlive;
    }

}

bool bumpBloc::react(struct controllerState** state, unsigned int elapsedTime)
{


    return true;
}

void bumpBloc::setDirection(float xMove, float yMove)
{
    this->dx=xMove;
    this->dy=yMove;
}