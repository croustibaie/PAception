//
// Created by croustibaie on 3/1/16.
//

#include "../headers/playerBloc.h"
#include "../headers/level.h"

playerBloc::playerBloc()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    this->xMove=0;
    this->yMove=0;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
}

playerBloc::playerBloc(SDL_Renderer **gRenderer, const char *path, level *l, int playerID, int x, int y)
{
    this->l=l;
    if (*gRenderer==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->playerID = playerID;
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
    this->speed=4;
    this->xMove=0;
    this->yMove=0;
    this->gRenderer=*gRenderer;
    this->myKind=PLAYER;
    loadMedia(&texture,gRenderer,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->lastShotTimer=0;
    this->currentTimer=0;
}

playerBloc::~playerBloc()
{

}

bool playerBloc::react(struct controllerState **state, unsigned int elapsedTime)
{

    int correctedSpeed= (int)(round((float)(speed)*(float)elapsedTime/20)); //We have to adapt the initial speed to the frame duration
    if (state == nullptr)
    {
        return true;
    }
    if (state[playerID]->RT)
    {
        int elapsedTime=SDL_GetTicks();
        elapsedTime-= lastShotTimer;
        if (elapsedTime>3000)
        {
            std::cout << "PAN" << std::endl;
            l->createBloc(LASER);
            lastShotTimer=SDL_GetTicks();
        }
    }
    xMove=(int)(correctedSpeed*(float)(state[playerID]->leftStickHorizontal)/32000);
    yMove=(int)(correctedSpeed*(float)(state[playerID]->leftStickVertical)/32000);
    if (xMove!=0 || yMove!=0)
    {
        return tryMove(xMove,yMove );
    }
    else return true;

}




void playerBloc::collisionReaction(bloc *b)
{
    if (b->kill())
    {
        std::cout<<"got killed"<<std::endl;
        this->l->deleteBloc(this->blocId);
        return ;
    }
    float tx,ty;
    tx=0;ty=0;
    int deltaX,deltaY;
    deltaX=0;deltaY=0;
    if ( xMove>0)
    {
        deltaX= b->getRect().x-(this->getRect().x+this->getRect().w)-1;
    }
    if (xMove<0)
    {
        deltaX=this->getRect().x-(b->getRect().x+b->getRect().w)-1;
    }
    if (yMove>0)
    {
        deltaY = b->getRect().y - (this->getRect().y+this->getRect().h)-1;
    }
    if (yMove<0)
    {
        deltaY= this->getRect().y - (b->getRect().y+b->getRect().h)-1;
    }
    if (xMove==0)
    {
        yMove= yMove==0 ? 0:yMove/(abs(yMove))*(deltaY);
        tryMove(0, yMove);
        return;
    }
    if (yMove==0)
    {
       xMove=  xMove==0 ? 0 : xMove/(abs(xMove))*(deltaX);
        tryMove(xMove,0 );
        return;
    }
    if (deltaX<0)
    {
        yMove= yMove == 0 ? 0: yMove/(abs(yMove))*(deltaY);
        tryMove(xMove, yMove );
        return;
    }
    if (deltaY<0)
    {
        xMove= xMove == 0 ? 0 : xMove/(abs(xMove))*(deltaX);
        tryMove(xMove ,yMove);
        return;
    }
    tx=deltaX/xMove;
    ty=deltaY/yMove;
    if (tx<ty)
    {
        xMove=xMove/(abs(xMove))*(deltaX);
        tryMove(xMove,yMove);
        return;
    }
    else
    {
        yMove=yMove/(abs(yMove))*(deltaY);
        tryMove(xMove,yMove);
        return;
    }
}