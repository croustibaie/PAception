//
// Created by croustibaie on 3/3/16.
//

#include "../headers/laserBloc.h"


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
    this->rect.w=50;
    this->rect.h=50;
    texture=NULL;
    this->speed=8;
    this->gRenderer=*gRenderer;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
}

laserBloc::~laserBloc()
{
}


bool laserBloc::tryMove(int x, int y)
{
    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    int xmove=x;
    int ymove=y;
    bloc* intersectedBloc = this->l->collide(this->blocId,a);
    if (intersectedBloc!= nullptr) //If there is a collision
    {

        this->collisionReaction(intersectedBloc);
        intersectedBloc->collisionReaction(this);
        return true;
    }
    else //Here we check that we're not trying to go out of the window
    {

        if (a.x+a.w>=SCREEN_WIDTH) //TODO : think about a strict or large inequality
        {
            xmove=xmove-(a.x+a.w-SCREEN_WIDTH);
            this->dx=- this->dx;
        }
        if (a.x<0)
        {
            this->dx=- this->dx;
            xmove=xmove-a.x;
        }
        if (a.y+a.h>SCREEN_HEIGHT) //TODO: Same as previously
        {
            this->dy=- this->dy;
            ymove=ymove-(a.y+a.h-SCREEN_HEIGHT);

        }
        if (a.y<0)
        {
            this->dy=- this->dy;
            ymove=ymove-a.y;
        }
        move(xmove,ymove);
    }
    return true;
}


bool laserBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    int xmove = (int)(speed*dx*float(elapsedTime)/20);
    int ymove = (int)(speed*dy*float(elapsedTime)/20);
    this->xMove=xmove;
    this->yMove=ymove;
    tryMove(xmove,ymove);
    return true;
}

void laserBloc::collisionReaction(bloc *b) {
    if (b->myKind != LASER) {

        return;
    }
    float tx, ty;
    tx = 0;
    ty = 0;
    int deltaX, deltaY;
    deltaX = 0;
    deltaY = 0;
    if (xMove > 0) {
        deltaX = b->getRect().x - (this->getRect().x + this->getRect().w) - 1;
    }
    if (xMove < 0) {
        deltaX = this->getRect().x - (b->getRect().x + b->getRect().w) - 1;
    }
    if (yMove > 0) {
        deltaY = b->getRect().y - (this->getRect().y + this->getRect().h) - 1;
    }
    if (yMove < 0) {
        deltaY = this->getRect().y - (b->getRect().y + b->getRect().h) - 1;
    }
    if ((xMove == 0) ) {
        yMove = yMove == 0 ? 0 : yMove / (abs(yMove)) * (deltaY);
        tryMove(0, yMove);
        return;
    }
    if ((yMove == 0) ) {
        xMove = xMove == 0 ? 0 : xMove / (abs(xMove)) * (deltaX);
        tryMove(xMove, 0);
        return;
    }
    if (deltaX<0)
    {
        yMove= yMove == 0 ? 0: -yMove/(abs(yMove))*(deltaY);
        tryMove(xMove, yMove );
        return;
    }
    if (deltaY<0)
    {
        xMove= xMove == 0 ? 0 : -xMove/(abs(xMove))*(deltaX);
        tryMove(xMove ,yMove);
        return;
    }
    tx = deltaX / xMove;
    ty = deltaY / yMove;
    if (tx < ty) {
        xMove = xMove / (abs(xMove)) * (deltaX);
        tryMove(xMove, yMove);
        return;
    }
    else {
        yMove = yMove / (abs(yMove)) * (deltaY);
        tryMove(xMove, yMove);
        return;
    }
}