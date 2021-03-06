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

playerBloc::playerBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, SDL_Texture* laserTexture,SDL_Texture* shieldTexture, level *l, int playerID,int teamID,int pPos, int x, int y) {
    this->l = l;
    if (*gRenderer == NULL)
    {
        std::cout << "In bloc constructor, no render" << std::endl;
    }
    this->playerID = playerID;
    if ((x < SCREEN_WIDTH - 50) && (y < SCREEN_HEIGHT - 50))
    {
        this->rect.x = x;
        this->rect.y = y;
    }
    else
    {
        this->rect.x = 0; //TODO : see for throwing an exception
        this->rect.y = 0;
    }
    this->dx=0;
    this->dy=0;
    this->rect.w = BLOCSIZE;
    this->rect.h = BLOCSIZE;
    texture = NULL;
    this->speed = INITIALSPEED;
    this->xMove = 0;
    this->yMove = 0;
    this->gRenderer = *gRenderer;
    this->myKind = PLAYER;
    this->reflect=false;
    this->texture=itexture;
    this->shieldTexture=shieldTexture;
    if (texture == NULL) {
        std::cout << "no texture loaded" << std::endl;
    }
    this->killOnTouch = false;
    this->blocId = nextBlocId;
    nextBlocId++;
    this->lastShotTimer = 0;
    for (int i = 0; i < NB_LASERS; i++)
    {
        this->laser[i] = laserBloc(gRenderer,laserTexture, l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
    this->ammo=MAX_AMMO;
    this->wallCollided=false;
    this->hp= PLAYER_HP;
    this->reloadTimer=0;
    this->shieldTimer=0;
    this->lastShieldTimer=0;
    this->shield=false;
    this->isBumped=false;
    this->teamNumber=teamID; //Make sure that everyone's team is different if teams are not set
    this->pPos=pPos;
    hpTexture=NULL;
    loadMedia(&hpTexture,gRenderer,"./textures/red.png");
    if (hpTexture==NULL)
    {
        std::cout<<"no HP texture loaded"<<std::endl;
    }
    heartTexture=NULL;
    loadMedia(&heartTexture,gRenderer,"./textures/heart.png");
    if (heartTexture==NULL)
    {
        std::cout<<"no Heart texture loaded"<<std::endl;
    }
    ammoTexture=NULL;
    loadMedia(&ammoTexture,gRenderer,"./textures/yellow.png");
    if (ammoTexture==NULL)
    {
        std::cout<<"no ammo texture loaded"<<std::endl;
    }
    bulletTexture=NULL;
    loadMedia(&bulletTexture,gRenderer,"./textures/bullet.png");
    if (bulletTexture==NULL)
    {
        std::cout<<"no bullet texture loaded"<<std::endl;
    }

}

playerBloc::~playerBloc()
{
}

bool playerBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    this->ignoredBlocs.clear();
    bloc* b=l->collide(this->blocId,this->getRect(),this->ignoredBlocs);
    if (b!= nullptr) //TODO: MAKE THIS A FUNCTION : Check_Initial_Collision
    {
        if(b->getKind()!=NONSOLID)
        {
            std::cout<<"Initial hit"<<std::endl;
            this->collisionReaction(b);
            std::cout<<"laser reacting"<<std::endl;
            b->collisionReaction(this);
            /*if((b->kill())&&(!(this->shield)))
            {
                l->deleteBloc(this->blocId, this->getKind()); //TODO: Change this to avoid instant kill
                return false;
            }
             */
        }
    }


    int correctedSpeed = (int) (round((float) (speed) * (float) elapsedTime / 20)); //We have to adapt the initial speed to the frame duration
    if (state == nullptr) {
        return true;
    }
    if (!getBumped())
    {
        xMove = (int) (correctedSpeed * (float) (state[playerID]->leftStickHorizontal) / 32000);
        yMove = (int) (correctedSpeed * (float) (state[playerID]->leftStickVertical) / 32000);
        int tmp=xMove;
        switch (pPos)
        {
            case 0:
                break;
            case 1:
                xMove=-yMove;
                yMove=tmp;
                break;
            case 2:
                xMove=-xMove;
                yMove=-yMove;
                break;
            case 3:
                xMove=yMove;
                yMove=-tmp;
                break;
        }
        setDirection((float) (state[playerID]->leftStickHorizontal) / 32000, (float) (state[playerID]->leftStickVertical) / 32000);
    }
    else
    {
        xMove = (int) (correctedSpeed * getdx());
        yMove = (int) (correctedSpeed * getdy());
    }

    bool isAlive;


    if (state[playerID]->RT)
    {
        this->shoot(state);
    }
    else
    {
        unsigned int time=SDL_GetTicks();
        if (time - this->reloadTimer>200)
        {
            this->reloadTimer=SDL_GetTicks();
            if (this->ammo<MAX_AMMO)
            {
                this->ammo++;
            }
        }
    }


    this->shield=false;

    if((state[playerID]->LT)&&(this->shieldTimer<SHIELD_MAX))
    {
        this->shield =true;
        std::cout<<"shield on"<<std::endl;
        this->shieldTimer=this->shieldTimer+elapsedTime;
        this->lastShieldTimer=SDL_GetTicks();
    }

    unsigned int time=SDL_GetTicks();

    if ((this->shield)&&(this->shieldTimer >= SHIELD_MAX)) //Shield not available anymore
    {
        this->shield = false;
        std::cout << "shield unavailable" << std::endl;
    }

    if ((time-this->lastShieldTimer>10000)&&(!(this->shield))&&(this->shieldTimer!=0)) //Time for the shield to be reloaded
    {
        this->shieldTimer = 0;
        std::cout << "shield available" << std::endl;
    }
    if (xMove != 0 || yMove != 0) {
        isAlive = tryMove(xMove, yMove);
    }
    else
    {
        isAlive = true;
    }


    return(isAlive);
}




bool playerBloc::collisionReaction(bloc *b)
{
    bool isAlive;
    enum edge touchededge=NONE; // edge of b touched by this bloc
    if(b->getKind()==NONSOLID)
    {
        ignoredBlocs.push_back(b);
        tryMove(this->xMove,this->yMove);
        return true;
    }
    if ((b->kill())&&(!(this->shield)))
    {
        this->hp--;
        if(hp==0)
        {
            std::cout << "got killed" << std::endl;
            this->l->deleteBloc(this->blocId,this->getKind());
            isAlive = false;
            return isAlive;
        }
        ignoredBlocs.push_back(b);
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

        if (yMove >0)
        {
            touchededge = UP;
        }
        else if (yMove<0)
        {
            touchededge=DOWN;
        }
        yMove= yMove==0 ? 0:yMove/(abs(yMove))*(deltaY);
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;

    }

    if (yMove==0)
    {

         if (xMove >0)
        {
            touchededge=LEFT;
        }

        else if (xMove<0)
        {
            touchededge=RIGHT;
        }
        xMove=  xMove==0 ? 0 : xMove/(abs(xMove))*(deltaX);
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;
    }

    if (deltaX<0)
    {

        if (yMove >0)
        {
            touchededge=UP;
        }

        else if (yMove<0)
        {
            touchededge=DOWN;
        }
         yMove= yMove == 0 ? 0: yMove/(abs(yMove))*(deltaY);
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;

    }
    if (deltaY<0)
    {

        if (xMove >0)
        {
            touchededge=LEFT;
        }

        else if (xMove<0)
        {
            touchededge=RIGHT;
        }
        xMove= xMove == 0 ? 0 : xMove/(abs(xMove))*(deltaX);
        if (touchededge==NONE)
        {
        }
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;

    }


    tx=deltaX/xMove;
    ty=deltaY/yMove;
    if (tx<ty)
    {
             if (xMove>0)
            {
                touchededge=LEFT;
            }
            else
            {
                touchededge=RIGHT;
            }

        xMove=xMove/(abs(xMove))*(deltaX);
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;
    }
    else
    {
         if (yMove>0)
            {
                touchededge=UP;
            }
            else
            {
                touchededge=DOWN;
            }
         yMove=yMove/(abs(yMove))*(deltaY);
        setBumped(b->bump(touchededge,this));
        isAlive=tryMove(xMove, yMove );
        return isAlive;
    }

}

void playerBloc::shoot( struct controllerState **state)
{
    int elapsedTime=SDL_GetTicks();
    elapsedTime-= lastShotTimer;
    if (elapsedTime>50 && ammo>0)
    {
        int x1 = state[playerID]->rightStickHorizontal;
        int y1 = state[playerID]->rightStickVertical;
        int tmp=x1;
        switch (pPos)
        {
            case 0:
                break;
            case 1:
                x1=-y1;
                y1=tmp;
                break;
            case 2:
                x1=-x1;
                y1=-y1;
                break;
            case 3:
                x1=y1;
                y1=-tmp;
                break;
        }
        if((x1==0)&&(y1==0))
        {
            return;
        }
        double ctheta =  x1/sqrt(double(x1*x1+y1*y1));
        double stheta =  y1/sqrt(double(x1*x1+y1*y1));
        double a = double(rect.w)/2.;
        double b = double(rect.h)/2.;
        int xPos,yPos;

        double r = sqrt(a*a + b*b);
        double rLaser = sqrt(double(LASER_HEIGHT/2*LASER_HEIGHT/2+LASER_WIDTH/2*LASER_WIDTH/2));
        xPos =(int)(rect.x + a + (r+rLaser+10)*ctheta);
        yPos =(int)(rect.y + b + (r+rLaser+10)*stheta);
        laser[nextLaser].setPosition(xPos,yPos);
        laser[nextLaser].setDirection(ctheta,stheta);

        l->insertBloc(&laser[nextLaser]);

        ammo--;
        nextLaser=(nextLaser+1)%NB_LASERS;
        lastShotTimer=SDL_GetTicks();
    }
}

void playerBloc::draw()
{

    if (texture == NULL) {
        std::cout << "no texture" << std::endl;
    }
    if (this->shield)
    {
        SDL_RenderCopy(gRenderer,shieldTexture,NULL,&rect);
    }
    else
    {
        SDL_RenderCopy(gRenderer, texture, NULL, &rect);
    }

    if (heartTexture == NULL) {
        std::cout << "no heart texture" << std::endl;
    }
    if (bulletTexture == NULL) {
        std::cout << "no bullet texture" << std::endl;
    }
    if (ammoTexture == NULL) {
        std::cout << "no ammo texture" << std::endl;
    }
    if (hpTexture == NULL) {
        std::cout << "no hp texture" << std::endl;
    }
    SDL_Rect rectBase;
    switch(playerID)
    {
        case 0:
            rectBase.x = 5;
            rectBase.y = 5;
            rectBase.w = 10;
            rectBase.h = 10;
            SDL_RenderCopy(gRenderer, heartTexture, NULL, &rectBase);
            for (int i = 1; i < hp + 1; i++) {
                rectBase.x = 5 + 10*i;
                SDL_RenderCopy(gRenderer, hpTexture, NULL, &rectBase);
            }
            rectBase.x = 5;
            rectBase.y = 30;
            SDL_RenderCopy(gRenderer, bulletTexture, NULL, &rectBase);
            rectBase.w = 5;
            for (int i = 1; i < ammo + 1; i++) {
                rectBase.x = 5 + 10*i;
                SDL_RenderCopy(gRenderer, ammoTexture, NULL, &rectBase);
            }
            break;
        case 3:
            rectBase.x = 5;
            rectBase.y = SCREEN_HEIGHT -10 -5 ;
            rectBase.w = 10;
            rectBase.h = 10;
            SDL_RenderCopyEx(gRenderer, heartTexture, NULL, &rectBase,180,NULL,SDL_FLIP_NONE);
            for (int i = 1; i < hp + 1; i++) {
                rectBase.x = 5 + 10*i;
                SDL_RenderCopy(gRenderer, hpTexture, NULL, &rectBase);
            }
            rectBase.x = 5;
            rectBase.y = SCREEN_HEIGHT - 10 - 30;
            SDL_RenderCopy(gRenderer, bulletTexture, NULL, &rectBase);
            rectBase.w = 5;
            for (int i = 1; i < ammo + 1; i++) {
                rectBase.x = 5 + 10*i;
                SDL_RenderCopy(gRenderer, ammoTexture, NULL, &rectBase);
            }
            break;
        case 1:
            rectBase.x = SCREEN_WIDTH -10 - 5;
            rectBase.y = 5;
            rectBase.w = 10;
            rectBase.h = 10;
            SDL_RenderCopy(gRenderer, heartTexture, NULL, &rectBase);
            for (int i = 1; i < hp + 1; i++) {
                rectBase.x =SCREEN_WIDTH -10 -( 5 + 10*i);
                SDL_RenderCopy(gRenderer, hpTexture, NULL, &rectBase);
            }
            rectBase.x = SCREEN_WIDTH -10 - 5;
            rectBase.y = 30;
            SDL_RenderCopy(gRenderer, bulletTexture, NULL, &rectBase);
            rectBase.w = 5;
            for (int i = 1; i < ammo + 1; i++) {
                rectBase.x = SCREEN_WIDTH -10 -( 5 + 10*i);
                SDL_RenderCopy(gRenderer, ammoTexture, NULL, &rectBase);
            }
            break;
        case 2:
            rectBase.x = SCREEN_WIDTH -10 - 5;
            rectBase.y = SCREEN_HEIGHT - 10 - 5;
            rectBase.w = 10;
            rectBase.h = 10;
            SDL_RenderCopyEx(gRenderer, heartTexture, NULL, &rectBase,180,NULL,SDL_FLIP_NONE);
            for (int i = 1; i < hp + 1; i++) {
                rectBase.x =SCREEN_WIDTH -10 -( 5 + 10*i);
                SDL_RenderCopy(gRenderer, hpTexture, NULL, &rectBase);
            }
            rectBase.x = SCREEN_WIDTH -10 - 5;
            rectBase.y = SCREEN_HEIGHT -10 - 30;
            SDL_RenderCopy(gRenderer, bulletTexture, NULL, &rectBase);
            rectBase.w = 5;
            for (int i = 1; i < ammo + 1; i++) {
                rectBase.x = SCREEN_WIDTH -10 -( 5 + 10*i);
                SDL_RenderCopy(gRenderer, ammoTexture, NULL, &rectBase);
            }
            break;
    }
}
void playerBloc::setDirection(float dirx, float diry )
{
    dx=dirx;
    dy=diry;
}

float playerBloc::getdx()
{
    return(dx);
}

float playerBloc::getdy()
{
    return(dy);
}

int playerBloc::getTeamNumber()
{
    return this->teamNumber;
}

void playerBloc::addHp(int hp)
{
  this->hp+=hp;
}
