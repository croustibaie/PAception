//
// Created by croustibaie on 3/1/16.
//

#include "../headers/playerBloc.h"
#include "../headers/level.h"
#include<math.h>

playerBloc::playerBloc()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    this->xMove=0;
    this->yMove=0;
    this->myKind=PLAYER;
    texture=NULL;
    gRenderer=NULL;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

playerBloc::playerBloc(SDL_Renderer **gRenderer, const char *path, level *l, int playerID, int x, int y) {
    this->l = l;
    if (*gRenderer == NULL) {
        std::cout << "In bloc constructor, no render" << std::endl;
    }
    this->playerID = playerID;
    if ((x < SCREEN_WIDTH - 50) && (y < SCREEN_HEIGHT - 50)) {
        this->rect.x = x;
        this->rect.y = y;
    }
    else {
        this->rect.x = 0; //TODO : see for throwing an exception
        this->rect.y = 0;
    }
    this->rect.w = 50;
    this->rect.h = 50;
    texture = NULL;
    this->speed = 8;
    this->xMove = 0;
    this->yMove = 0;
    this->gRenderer = *gRenderer;
    this->myKind = PLAYER;
    loadMedia(&texture, gRenderer, path);
    if (texture == NULL) {
        std::cout << "no texture loaded" << std::endl;
    }
    killOnTouch = false;
    this->blocId = nextBlocId;
    nextBlocId++;
    this->lastShotTimer = 0;
    for (int i = 0; i < 20; i++)
    {
        this->laser[i] = new laserBloc(gRenderer, "./dead.bmp", l, 50, 50, 1, 1);
    }
    this->nextLaser=0;
    this->wallCollided=false;
}

playerBloc::~playerBloc()
{
    for (int i=0;i<20;i++)
    {
        delete laser[i];
    }
}

bool playerBloc::react(struct controllerState **state, unsigned int elapsedTime) {

    int correctedSpeed = (int) (round(
            (float) (speed) * (float) elapsedTime / 20)); //We have to adapt the initial speed to the frame duration
    if (state == nullptr) {
        return true;
    }

    xMove = (int) (correctedSpeed * (float) (state[playerID]->leftStickHorizontal) / 32000);
    yMove = (int) (correctedSpeed * (float) (state[playerID]->leftStickVertical) / 32000);
    bool isAlive;
    if (xMove != 0 || yMove != 0) {
        isAlive = tryMove(xMove, yMove);

    }
    else
    {
        isAlive = true;
    }

    if (state[playerID]->RT) {
        this->shoot(state);
    }

    return(isAlive);
}




bool playerBloc::collisionReaction(bloc *b)
{
    bool isAlive;
    if (b->kill())
    {
        std::cout<<"got killed"<<std::endl;
        this->l->deleteBloc(this->blocId);
        isAlive=false;
        return isAlive;
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
        isAlive=tryMove(0, yMove);
        return isAlive;
    }
    if (yMove==0)
    {
       xMove=  xMove==0 ? 0 : xMove/(abs(xMove))*(deltaX);
        isAlive=tryMove(xMove,0 );
        return isAlive;
    }
    if (deltaX<0)
    {
        yMove= yMove == 0 ? 0: yMove/(abs(yMove))*(deltaY);
        isAlive=tryMove(xMove, yMove );
        return isAlive;
    }
    if (deltaY<0)
    {
        xMove= xMove == 0 ? 0 : xMove/(abs(xMove))*(deltaX);
        isAlive=tryMove(xMove ,yMove);
        return isAlive;
    }
    tx=deltaX/xMove;
    ty=deltaY/yMove;
    if (tx<ty)
    {
        xMove=xMove/(abs(xMove))*(deltaX);
        isAlive=tryMove(xMove,yMove);
        return isAlive;
    }
    else
    {
        yMove=yMove/(abs(yMove))*(deltaY);
        isAlive=tryMove(xMove,yMove);
        return isAlive;
    }
}

void playerBloc::shoot( struct controllerState **state)
{
    int elapsedTime=SDL_GetTicks();
    elapsedTime-= lastShotTimer;
    if (elapsedTime>300)
    {
        std::cout << "PAN" << std::endl;
        int x1 = state[playerID]->rightStickHorizontal;
        int y1 = state[playerID]->rightStickVertical;
        if((x1==0)&&(y1==0))
        {
            return;
        }
        double ctheta =  x1/sqrt(double(x1*x1+y1*y1));
        double stheta =  y1/sqrt(double(x1*x1+y1*y1));
        //int sgx = x1 == 0 ? 0 : x1/(abs(x1));
        //int sgy = y1 == 0 ? 0 : y1/(abs(y1));
        double a = double(rect.w)/2.;
        double b = double(rect.h)/2.;
        //double lambda = atan(b/a);
        int xPos,yPos;
        double r = sqrt(a*a + b*b);

        /*if(fabs(stheta)<=sin(lambda))
        {
            switch(sgx) {
                case -1 :
                    xPos = rect.x - 1 - LASER_WIDTH;
                    break;
                case 0 :
                    xPos = (int) (rect.x + a);
                    break;
                case 1 :
                    xPos = rect.x + rect.w +1;
                    break;
            }
        }
        else
        {
            xPos= (int)(rect.x + b*ctheta/stheta);
        }
        if(fabs(ctheta)<=cos(lambda))
        {
            switch(sgy) {
                case -1 :
                    yPos = rect.y - 1 - LASER_HEIGHT;
                    break;
                case 0 :
                    yPos = (int) (rect.y + b);
                    break;
                case 1 :
                    yPos = rect.y + rect.h +1;
                    break;
            }
        }
        else
        {
            yPos=(int)(rect.y  + a*stheta/ctheta );
        }*/
        double rLaser = sqrt(double(LASER_HEIGHT*LASER_HEIGHT+LASER_WIDTH*LASER_WIDTH));
        xPos =(int)(rect.x + a + (r+rLaser+1)*ctheta);
        yPos =(int)(rect.y + b + (r+rLaser+1)*stheta);
        laser[nextLaser]->setPosition(xPos,yPos);
        laser[nextLaser]->setDirection(ctheta,stheta);
        l->insertBlocs(laser[nextLaser],1);
        nextLaser=(nextLaser+1)%20;
        //l->createBloc(LASER);
        lastShotTimer=SDL_GetTicks();
    }
}