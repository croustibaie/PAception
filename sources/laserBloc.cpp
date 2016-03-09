//
// Created by croustibaie on 3/3/16.
//

#include "../headers/laserBloc.h"
#include "../headers/level.h"

laserBloc::laserBloc()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    this->xMove=0; //direction of the bloc following x axis
    this->yMove=0; //direction of the bloc following y axis
    this->myKind=LASER;
    texture=NULL;
    gRenderer=NULL;
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

laserBloc::laserBloc(SDL_Renderer **gRenderer, const char *path, level *l,int x,int y,int dx,int dy)
{
    this->dx=(float)(dx/sqrt((double)(dx*dx+dy*dy)));
    this->dy=(float)(dy/sqrt((double)(dx*dx+dy*dy)));
    this->xMove=dx;
    this->yMove=dy;
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
    this->rect.w=LASER_WIDTH;
    this->rect.h=LASER_HEIGHT;
    texture=NULL;
    this->speed=10;
    this->gRenderer=*gRenderer;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

laserBloc::~laserBloc()
{
}




bool laserBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    if (l->collide(this->blocId,this->getRect())!= nullptr)
    {
        l->deleteBloc(this->blocId);
        return false;
    }
    int xmove = (int)(speed*dx*float(elapsedTime)/20);
    int ymove = (int)(speed*dy*float(elapsedTime)/20);
    this->xMove=xmove;
    this->yMove=ymove;
    return tryMove(this->xMove,this->yMove);
}

bool laserBloc::collisionReaction(bloc *b)
{
    bool isAlive;
    if (b->getKind()!=STATIC)
    {
        this->l->deleteBloc(this->blocId);
        isAlive=false;
        return isAlive;
    }
    float tx, ty;
    tx = 0;
    ty = 0;
    int deltaX, deltaY;
    deltaX = 0;
    deltaY = 0;
    if (xMove > 0)
    {
        deltaX = b->getRect().x - (this->getRect().x + this->getRect().w) - 1;
    }
    if (xMove < 0)
    {
        deltaX = this->getRect().x - (b->getRect().x + b->getRect().w) - 1;
    }
    if (yMove > 0)
    {
        deltaY = b->getRect().y - (this->getRect().y + this->getRect().h) - 1;
    }
    if (yMove < 0)
    {
        deltaY = this->getRect().y - (b->getRect().y + b->getRect().h) - 1;
    }
    if ((xMove == 0) )
    {
        yMove = yMove == 0 ? 0 : -yMove / (abs(yMove)) * (deltaY);
        dy=-dy;
        isAlive=tryMove(0, yMove);
        return isAlive;
    }
    if ((yMove == 0) ) {
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

bool laserBloc::wallCollision(SDL_Rect a)
{
    this->wallCollided=false;
    if (a.x+a.w>SCREEN_WIDTH)
    {
        xMove=xMove-(a.x+a.w-SCREEN_WIDTH);
        this->dx=- this->dx;
        this->wallCollided=true;
    }
    if (a.x<0)
    {
        this->dx=- this->dx;
        xMove=xMove-a.x;
        this->wallCollided=true;
    }
    if (a.y+a.h>SCREEN_HEIGHT)
    {
        this->dy=- this->dy;
        yMove=yMove-(a.y+a.h-SCREEN_HEIGHT);
        this->wallCollided=true;

    }
    if (a.y<0)
    {
        this->dy=- this->dy;
        yMove=yMove-a.y;
        this->wallCollided=true;
    }
return this->wallCollided;
}

void laserBloc::setDirection(float xMove, float yMove)
{
    this->dx=xMove;
    this->dy=yMove;
}