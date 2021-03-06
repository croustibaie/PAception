//
// Created by croustibaie on 3/3/16.
//

#include "../headers/laserBloc.h"
#include "../headers/level.h"
#include <math.h>

laserBloc::laserBloc()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    this->xMove=0; //direction of the bloc following x axis
    this->yMove=0; //direction of the bloc following y axis
    this->myKind=SOLID;
    texture=NULL;
    gRenderer=NULL;
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

laserBloc::laserBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, level *l,int x,int y,int dx,int dy)
{
    this->isBumped=false;
    this->dx=(float)(dx/sqrt((double)(dx*dx+dy*dy)));
    this->dy=(float)(dy/sqrt((double)(dx*dx+dy*dy)));
    this->xMove=dx;
    this->yMove=dy;
    this->l=l;
    this->shield=false;
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
    this->speed=14;
    this->gRenderer=*gRenderer;
    this->texture=itexture;
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=true;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->myKind=SOLID;
    this->reflect=false;
}

laserBloc::~laserBloc()
{
}


bool laserBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    bloc* firstIntersect = l->collide(this->blocId,this->getRect(),this->getIgnoredBlocs());
    if (firstIntersect!= nullptr )
    {
        if (firstIntersect->getKind()!=NONSOLID)
        {
            std::cout << "In laserreact: initial hit" << std::endl;
            firstIntersect->collisionReaction(this);
            l->deleteBloc(this->blocId, this->getKind());
            return false;
        }
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
    if (!(b->isReflector()))
    {
        if ((b->getKind()==SOLID) || (b->getKind()==PLAYER && !(b->shieldState())))
        {
            std::cout<<"laser deleting"<<std::endl;
            this->l->deleteBloc(this->blocId, this->getKind());
            isAlive = false;
            return isAlive;
        }
    }
    if (b->getKind()==NONSOLID)
    {
        ignoredBlocs.push_back(b);
        return tryMove(xMove,yMove);
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

bool laserBloc::tryMove(int x, int y)
{
    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    bool isAlive=true;
    bloc* intersectedBloc = this->l->collide(this->blocId,a,this->ignoredBlocs);
    if (intersectedBloc!= nullptr) //If there is a collision
    {

        isAlive=this->collisionReaction(intersectedBloc);
        intersectedBloc->collisionReaction(this);
        return isAlive;
    }
    else //Here we check that we're not trying to go out of the window
    {
        if(wallCollision(a))
        {
            l->deleteBloc(this->blocId,this->getKind());
            return false;
        }
        else
        {
            move(xMove,yMove);
            this->xMove=0;
            this->yMove=0;
        }
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

void laserBloc::setDirection(float dx, float dy)
{
    this->dx=dx;
    this->dy=dy;
}

void laserBloc::draw()
{
    SDL_Rect textureRect;
    textureRect.x= this->rect.x-this->getRect().w/2;
    textureRect.w=2*this->rect.w;
    textureRect.y=this->rect.y;
    textureRect.h=this->rect.h;

    SDL_Point center;
    center.x=this->rect.w/4*3;
    center.y=this->rect.h/2;

    double angle;
    if (this->dy>=0)
    {
        angle=acos((this->dx/sqrt(this->dx*this->dx+this->dy*this->dy)));
    }
    else
    {
        angle=-acos((this->dx/sqrt(this->dx*this->dx+this->dy*this->dy)));
    }
    angle = angle*180/M_PI;
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
    SDL_RenderCopyEx(gRenderer,texture, NULL, &textureRect,angle,&center,SDL_FLIP_NONE );
    //SDL_RenderCopy(gRenderer,texture, NULL, &textureRect);
}
