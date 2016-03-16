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

playerBloc::playerBloc(SDL_Renderer **gRenderer, level *l, int playerID,int teamID, int x, int y) {
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
    this->speed = INITIALSPEED;
    this->xMove = 0;
    this->yMove = 0;
    this->gRenderer = *gRenderer;
    this->myKind = PLAYER;
    loadMedia(&texture, gRenderer, "./textures/square2.png");
    if (texture == NULL) {
        std::cout << "no texture loaded" << std::endl;
    }
    this->killOnTouch = false;
    this->blocId = nextBlocId;
    nextBlocId++;
    this->lastShotTimer = 0;
    for (int i = 0; i < NB_LASERS; i++)
    {
        this->laser[i] = new laserBloc(gRenderer, "./textures/black.bmp", l, 50, 50, 1, 0);
    }
    this->nextLaser=0;
    this->ammo=MAX_AMMO;
    this->wallCollided=false;
    this->hp= PLAYER_HP;
    this->reloadTimer=0;
    switch(playerID)
    {
        case 0:
        for(int i = 0;i<MAX_AMMO+PLAYER_HP+2;i++)
        {

                if (i < PLAYER_HP + 1)
                {
                    this->rectBase[i].x = 5 + 10*i;
                    this->rectBase[i].y = 5;
                    this->rectBase[i].w = 10;
                    this->rectBase[i].h = 10;
                }
                else
                {
                    this->rectBase[i].x = 5 + 10*(i-PLAYER_HP-1);
                    this->rectBase[i].y = 30;
                    if(i==PLAYER_HP+1)
                    {
                        this->rectBase[i].w=10;
                    }
                    else
                    {
                        this->rectBase[i].w = 5;
                    }
                    this->rectBase[i].h = 10;
                }

        }
        break;

        case 1:
            for(int i = 0;i<MAX_AMMO+PLAYER_HP+2;i++)
            {

                if (i < PLAYER_HP + 1)
                {
                    this->rectBase[i].x = 5 + 10*i;
                    this->rectBase[i].y = SCREEN_HEIGHT -10 - 5;
                    this->rectBase[i].w = 10;
                    this->rectBase[i].h = 10;
                }
                else
                {
                    this->rectBase[i].x = 5 + 10*(i-PLAYER_HP-1);
                    this->rectBase[i].y = SCREEN_HEIGHT - 10 -30;
                    if(i==PLAYER_HP+1)
                    {
                        this->rectBase[i].w=10;
                    }
                    else
                    {
                        this->rectBase[i].w = 5;
                    }
                    this->rectBase[i].h = 10;
                }

            }
            break;

        case 2:
            for(int i = 0;i<MAX_AMMO+PLAYER_HP+2 ; i++) {

                if (i < PLAYER_HP + 1) {
                    this->rectBase[i].x = SCREEN_WIDTH - 10 - 5 - 10 * i;
                    this->rectBase[i].y = 5;
                    this->rectBase[i].w = 10;
                    this->rectBase[i].h = 10;
                }
                else {
                    this->rectBase[i].x = SCREEN_WIDTH - 10 - 5 - 10 * (i - PLAYER_HP - 1);
                    this->rectBase[i].y = 30;
                    if (i == PLAYER_HP + 1) {
                        this->rectBase[i].w = 10;
                    }
                    else {
                        this->rectBase[i].w = 5;
                    }
                    this->rectBase[i].h = 10;
                }
            }

            break;

        case 3:
                    for (int i = 0; i < MAX_AMMO + PLAYER_HP + 2; i++) {

                        if (i < PLAYER_HP + 1) {
                            this->rectBase[i].x = SCREEN_WIDTH - 10 - 5 - 10 * i;
                            this->rectBase[i].y = SCREEN_HEIGHT - 10 - 5;
                            this->rectBase[i].w = 10;
                            this->rectBase[i].h = 10;
                        }
                        else {
                            this->rectBase[i].x = SCREEN_WIDTH - 10 - 5 - 10 * (i - PLAYER_HP - 1);
                            this->rectBase[i].y = SCREEN_HEIGHT -10 - 30;
                            if (i == PLAYER_HP + 1) {
                                this->rectBase[i].w = 10;
                            }
                            else {
                                this->rectBase[i].w = 5;
                            }
                            this->rectBase[i].h = 10;
                        }
                    }
            break;
            }

    this->teamNumber=teamID; //Make sure that everyone's team is different if teams are not set
    hpTexture=NULL;
    loadMedia(&hpTexture,gRenderer,"./textures/red.bmp");
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
    for (int i=0;i<NB_LASERS;i++)
    {
        delete laser[i];
    }
}

bool playerBloc::react(struct controllerState **state, unsigned int elapsedTime)
{
    this->ignoredBlocs.clear();
    bloc* b=l->collide(this->blocId,this->getRect(),this->ignoredBlocs);
    if (b!= nullptr) //TODO: MAKE THIS A FUNCTION : Check_Initial_Collision
    {
        if(b->getKind()!=NONSOLID)
        {
            l->deleteBloc(this->blocId,this->getKind());
            return false;
        }
    }
    int correctedSpeed = (int) (round((float) (speed) * (float) elapsedTime / 20)); //We have to adapt the initial speed to the frame duration
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

    if (state[playerID]->RT)
    {
        this->shoot(state);
    }
    else
    {
        unsigned int time=SDL_GetTicks();
        if (time - this->reloadTimer>1000)
        {
            this->reloadTimer=SDL_GetTicks();
            if (this->ammo<MAX_AMMO)
            {
                this->ammo++;
            }
        }
    }
    //std::cout<<"ammo :"<< this->ammo<<std::endl;
    return(isAlive);
}




bool playerBloc::collisionReaction(bloc *b)
{
    bool isAlive;
    if(b->getKind()==NONSOLID)
    {
        ignoredBlocs.push_back(b);
        tryMove(this->xMove,this->yMove);
        return true;
    }
    if (b->kill())
    {
        this->hp--;
        if(hp==0)
        {
            std::cout << "got killed" << std::endl;
            this->l->deleteBloc(this->blocId,this->getKind());
            isAlive = false;
            return isAlive;
        }
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
    if (elapsedTime>300 && ammo>0)
    {
        int x1 = state[playerID]->rightStickHorizontal;
        int y1 = state[playerID]->rightStickVertical;
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
        xPos =(int)(rect.x + a + (r+rLaser+1)*ctheta);
        yPos =(int)(rect.y + b + (r+rLaser+1)*stheta);
        laser[nextLaser]->setPosition(xPos,yPos);
        laser[nextLaser]->setDirection(ctheta,stheta);

        l->insertBloc(laser[nextLaser]);

        ammo--;
        nextLaser=(nextLaser+1)%NB_LASERS;
        lastShotTimer=SDL_GetTicks();
    }
}

void playerBloc::draw()
{
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
    SDL_RenderCopy(gRenderer,texture, NULL, &rect );
    if (heartTexture==NULL)
    {
        std::cout<<"no heart texture"<<std::endl;
    }
    SDL_RenderCopy(gRenderer,heartTexture, NULL, &rectBase[0] );
    if (hpTexture==NULL)
    {
        std::cout<<"no hp texture"<<std::endl;
    }
    for(int i =1;i<hp+1;i++)
    {
        SDL_RenderCopy(gRenderer,hpTexture, NULL, &rectBase[i] );
    }
    if (bulletTexture==NULL)
    {
        std::cout<<"no bullet texture"<<std::endl;
    }
    SDL_RenderCopy(gRenderer,bulletTexture, NULL, &rectBase[PLAYER_HP+1] );
    if (ammoTexture==NULL)
    {
        std::cout<<"no ammo texture"<<std::endl;
    }
    for(int i =PLAYER_HP+2;i<PLAYER_HP+ammo+2;i++)
    {
        SDL_RenderCopy(gRenderer,ammoTexture, NULL, &rectBase[i] );
    }
}