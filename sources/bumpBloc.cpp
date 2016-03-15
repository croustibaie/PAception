//
// Created by emilien on 11/03/16.
//




#include "../headers/level.h"
#include "../headers/playerBloc.h"
#include "../headers/bumpBloc.h"
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
    this->bumpingedge=NONE;
}

bumpBloc::bumpBloc(SDL_Renderer **gRenderer, level *l,int x,int y,float dx,float dy)
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
    loadMedia(&texture,gRenderer,"./textures/cannabis.bmp");
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->bumpingedge=NONE;
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
    if(b->getKind()==NONSOLID)
    {
        ignoredBlocs.push_back(b);
        tryMove(this->xMove,this->yMove);
        return true;
    }

    if(b->getKind()==PLAYER && b->getxMove()==0 && b->getyMove()==0)

    {
         // edge of the bumpBloc touched by the player
        // warning : it is the contrary to what it is in the playerBloc's collisionReaction
        enum edge touchededge =NONE;
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


        if (xMove == 0)
        {
            yMove = yMove == 0 ? 0 : yMove / (abs(yMove)) * (deltaY);

            if (yMove >0)
            {
                touchededge = DOWN;
            }
        else if (yMove<0)
            {
                touchededge = UP;
            }
           b->setBumped(bump(touchededge,b));
            isAlive=tryMove(xMove,yMove );
            return isAlive;
        }

        if (yMove == 0)
        {
            xMove = xMove == 0 ? 0 : xMove / (abs(xMove)) * (deltaX);

            if (xMove >0)
            {
                touchededge=RIGHT;
            }

        else if (xMove<0)
            {
                touchededge=LEFT;
            }
            b->setBumped(bump(touchededge,b));
            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }


        if (deltaX < 0)
        {
            yMove = yMove == 0 ? 0 : yMove / (abs(yMove)) * (deltaY);

            if (yMove >0)
            {
                touchededge=DOWN;
            }

            else if (yMove<0)
            {
                touchededge=UP;
            }

            b->setBumped(bump(touchededge,b));
            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }

        if (deltaY < 0)
        {
            xMove = xMove == 0 ? 0 : xMove / (abs(xMove)) * (deltaX);

            if (xMove >0)
            {
                touchededge=RIGHT;
            }

            else if (xMove<0)
            {
                touchededge=LEFT;
            }
            b->setBumped(bump(touchededge,b));
            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }

        tx = deltaX / xMove;
        ty = deltaY / yMove;
        if (tx < ty)
        {
            xMove = xMove / (abs(xMove)) * (deltaX);
            if (xMove>0)
            {
                touchededge=RIGHT;
            }
            else
            {
                touchededge=LEFT;
            }
        }
        else
        {
            yMove = yMove / (abs(yMove)) * (deltaY);
             if (yMove>0)
            {
                touchededge=DOWN;
            }
            else
            {
                touchededge=UP;
            }

        }

        b->setBumped(bump(touchededge,b));
        isAlive = tryMove(xMove, yMove);
        return isAlive;
    }
}

bool bumpBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
bloc* blocarray[bumpedbloc.size()];
    int tmp=0;
    std::map<bloc*,unsigned int>::iterator it;
    for (it=bumpedbloc.begin(); it!=bumpedbloc.end();it++)
    {
        if (SDL_GetTicks()-it->second>=BUMPTIME) // after a time of FREEZETIME ms sets the speed of a frozen bloc to INITIALSPEED
        {
            if ((it->first)->getKind()==PLAYER )
            {
                std::cout << "end of bumping" << std::endl;

                (it->first)->setBumped(false);
                blocarray[tmp] = it->first;
                tmp++;
            }
        }
    }
    for (int i=0; i<tmp;i++)
    {
        bumpedbloc.erase(blocarray[i]);
    }

    return true;
}

void bumpBloc::setDirection(float xMove, float yMove)
{
    this->dx=xMove;
    this->dy=yMove;
}
float bumpBloc::getdx()
{
    return(dx);
};

float bumpBloc::getdy()
{
    return(dy);
};
bool bumpBloc::bump(enum edge touchededge,bloc* b) // touchededge is the edge of the bumpbloc touched by the bloc b

{

   if( b->getKind()==PLAYER )
   {
       if (touchededge == bumpingedge)
       {
            switch (touchededge) // the bumpBloc wins
           {
                case UP :

                   b->setDirection(0,dy);
                    break;

                case DOWN :
                   b->setDirection(0,dy);
                   break;

                case LEFT :
                   b->setDirection(dx,0);
                    break;

                case RIGHT  :
                   b->setDirection(dx,0);
                    break;

                case NONE  :
                std::cout<<"error : les deux blocs sont immobiles et rentrent en collision"<<std::endl ;
                    break;
           }
           setDirection(0,0);
           xMove=0;
           yMove=0;
           return(true);
       }

       else
       {
            switch (touchededge) // the bloc b wins if touchededge!=NONE
           {
                case UP :
                    setDirection(0,b->getdy());
                    break;
                case DOWN :
                    setDirection(0,b->getdy());
                    break;
                case LEFT :
                    setDirection(b->getdx(),0);
                    break;

                case RIGHT :
                    setDirection(b->getdx(),0);
                    break;

               case NONE : // in this particular case the bloc b doesn't move
                   std::cout<<"error : cas inattendu"<<std::endl ;
                   break;

           }
           return(false);
       }
   }
};


