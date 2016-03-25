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
    this->speed=6;
    this->acceleration=float(-0.03);
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

bumpBloc::bumpBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, level *l,int x,int y,float dx,float dy)
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
    this->rect.w=BLOCSIZE;
    this->rect.h=BLOCSIZE;
    texture=NULL;
    this->speed=BUMPSPEED;
    this->evolvingspeed=float(6);
    this->acceleration=float(-0.05);
    this->xMove=0;
    this->yMove=0;
    this->isBumped=false;
    this->dx=(float)(0);
    this->dy=(float)(0);
    this->gRenderer=*gRenderer;
    this->myKind=SOLID;
    this->texture=itexture;
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
    this->bumpingedge=NONE;
    this->reflect=false;
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
         return tryMove(this->xMove,this->yMove);
    }
    if (b->kill()) // If we hit a laser
    {
        ignoredBlocs.push_back(b);
        return tryMove(this->xMove,this->yMove);
    }
    if (b->getKind()==SOLID)
    {
        bumpingedge=NONE;
        setDirection(0,0);
    }

         // edge of the bumpBloc touched by the player
        // warning : it is the contrary to what it is in the playerBloc's collisionReaction
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
            isAlive=tryMove(xMove,yMove);
            return isAlive;
        }

        if (yMove == 0)
        {

            xMove = xMove == 0 ? 0 : xMove / (abs(xMove)) * (deltaX);
            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }


        if (deltaX < 0)
        {
            yMove = yMove == 0 ? 0 : yMove / (abs(yMove)) * (deltaY);

            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }

        if (deltaY < 0)
        {
            xMove = xMove == 0 ? 0 : xMove / (abs(xMove)) * (deltaX);
            isAlive = tryMove(xMove,yMove);
            return isAlive;
        }

        tx = deltaX / xMove;
        ty = deltaY / yMove;
        if (tx < ty)
        {

             xMove = xMove / (abs(xMove)) * (deltaX);
        }
        else
        {

             yMove = yMove / (abs(yMove)) * (deltaY);
        }

    tryMove(xMove, yMove);

    return true;  // the bumpBloc can't die
}

bool bumpBloc::react(struct controllerState** state, unsigned int elapsedTime)
{
    // gestion of the bumped blocs
    ignoredBlocs.clear();
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

    // gestion of the movement

    this->ignoredBlocs.clear();
    bloc* b=l->collide(this->blocId,this->getRect(),this->ignoredBlocs);
    if (b!= nullptr) //TODO: MAKE THIS A FUNCTION : Check_Initial_Collision
    {
        if(b->getKind()!=NONSOLID)
        {
           this->ignoredBlocs.push_back(b);
        }
    }


    if (bumpingedge!=NONE)// ie the bloc has been touched
    {
         evolvingspeed =  (this->evolvingspeed) + this->acceleration * ((float) elapsedTime) / 20; // acceleration phase with negative acceleration

        if (evolvingspeed < 0)
        {
           evolvingspeed = 0;
            bumpingedge=NONE;
        }

    }
    else
    {
        evolvingspeed=(float) speed;
    }


    int correctedSpeed = (int) ((round(evolvingspeed) * (float) elapsedTime / 20)); //We have to adapt the initial speed to the frame duration
    xMove = (int) (correctedSpeed * getdx());
    yMove = (int) (correctedSpeed * getdy());

    if (xMove==0 && yMove==0)
    {
        setDirection(0,0);
        bumpingedge=NONE;
    }
    return tryMove(xMove, yMove);
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
                   b->setDirection(0,-1);
               std::cout<<"the bumpBloc wins : UP"<< std::endl;
                    break;

                case DOWN :
                   b->setDirection(0,1);
                   std::cout<<"the bumpBloc wins : DOWN"<< std::endl;
                   break;

                case LEFT :
                   b->setDirection(-1,0);
                   std::cout<<"the bumpBloc wins : LEFT"<< std::endl;
                    break;

                case RIGHT  :
                   b->setDirection(1,0);
                   std::cout<<"the bumpBloc wins : RIGHT"<< std::endl;
                    break;

                case NONE  :
                std::cout<<"error : les deux blocs sont immobiles et rentrent en collision"<<std::endl ;
                   return(false);
                    break;
           }
           setDirection(0,0);
           bumpingedge=NONE;
           bumpedbloc.insert(std::pair<bloc*,unsigned int>(b,SDL_GetTicks()));
           return(true);
       }

       else
       {
            switch (touchededge) // the bloc b wins if touchededge!=NONE
           {
                case UP :
                    this->evolvingspeed=this->speed;
                    std::cout<<"in bump"<<std::endl;
                    setDirection(0,1);
                   bumpingedge=DOWN;
                   std::cout<<"bumpingedge : DOWN"<<std::endl;
                    break;
                case DOWN :
                    this->evolvingspeed=this->speed;
                    std::cout<<"in bump"<<std::endl;
                    setDirection(0,-1);
                    bumpingedge=UP;
                    std::cout<<"bumpingedge : UP"<<std::endl;
                    break;
                case LEFT :
                    this->evolvingspeed=this->speed;
                    std::cout<<"in bump"<<std::endl;
                    setDirection(1,0);
                   bumpingedge=RIGHT;
                    std::cout<<"bumpingedge : RIGHT"<<std::endl;
                    break;

                case RIGHT :
                    this->evolvingspeed=this->speed;
                    std::cout<<"in bump"<<std::endl;
                    setDirection(-1,0);
                   bumpingedge=LEFT;
                    std::cout<<"bumpingedge : LEFT"<<std::endl;
                    break;

               case NONE : // in this particular case the bloc b doesn't move
                   std::cout<<"error : cas inattendu"<<std::endl ;
                   switch (bumpingedge) // the bloc b wins if touchededge!=NONE
                    {

                       case UP :

                           b->setDirection(0,-1);
                           std::cout<<"the bumpBloc wins : UP"<<std::endl;
                           break;
                       case DOWN :

                           b->setDirection(0,1);
                           std::cout<<"the bumpBloc wins : DOWN"<<std::endl;
                           break;
                       case LEFT :

                           b->setDirection(-1,0);
                           std::cout<<"the bumpBloc wins : LEFT"<<std::endl;
                           break;
                       case RIGHT :

                           b->setDirection(1,0);
                           std::cout<<"the bumpBloc wins : LEFT"<<std::endl;
                           break;

                       case NONE : // in this particular case the bloc b doesn't move
                           std::cout<<"error : les deux blocs sont immobiles et rentrent en collision"<<std::endl ;

                           break;

                   }
                   setDirection(0,0);
                    bumpingedge=NONE;
                    bumpedbloc.insert(std::pair<bloc*,unsigned int>(b,SDL_GetTicks()));
                    return(true);
           }
           return(false);
       }
   }
};



