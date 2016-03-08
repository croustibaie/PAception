//
// Created by croustibaie on 12/14/15.
//

#include "../headers/level.h"

unsigned int bloc::nextBlocId=0;

// Default constructor

bloc::bloc ()
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
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided=false;
}

// Parametrized constructor

bloc::bloc (SDL_Renderer** gRender,const char* path, level* l, int x, int y)
{
    this->l=l;
    if (*gRender==NULL)
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
    this->speed=16;
    this->xMove=0;
    this->yMove=0;
    this->gRenderer=*gRender;
    loadMedia(&texture,gRender,path);
    if (texture==NULL)
    {
        std::cout<<"no texture loaded"<<std::endl;
    }
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
    this->wallCollided;
}



// Destructor

bloc::~bloc()
{
}

bool bloc::react(struct controllerState** state,unsigned int elapsedTime)//This class is overcharged, bloc::react should never be used
{
    return true;
}

// Display block

void bloc::draw()
{
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
    SDL_RenderCopy(gRenderer,texture, NULL, &rect );
}

// Move attempt

bool bloc::tryMove(int x, int y)
{
    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    bool isAlive=true;
    bloc* intersectedBloc = this->l->collide(this->blocId,a);
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
            isAlive=tryMove(this->xMove,this->yMove);
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

// Displacement

void bloc::move(int x , int y)
{
    this->rect.x+=x;
    this->rect.y+=y;
}

// Modify speed

void bloc::setSpeed(int speed)
{
    this->speed=speed;
}

// Determine bloc type

int bloc::getBlocId() const
{
    return blocId;
}

// Get SDL Renderer

 SDL_Renderer* bloc::getRenderer() const
{
    return gRenderer;
}

// Get bloc texture

SDL_Texture* bloc::getTexture() const
{
    return texture;
}

// Get bloc dimensions

SDL_Rect bloc::getRect() const
{
    return rect;
}

// Get bloc speed

int bloc::getSpeed() const
{
    return speed;
}

bool bloc::collisionReaction(bloc *b) // Method used for static blocs
{
    return tryMove(0,0);
}

// Kill bloc

bool bloc::kill()
{
    return killOnTouch;
}

bool bloc::wallCollision(SDL_Rect a)
{
    this->wallCollided=false; //This variable is a bit ugly, it is used to know whether we hit the wall. Reset at every tryMove
    if (a.x+a.w>SCREEN_WIDTH)//Hit the right wall
    {
        this->xMove=SCREEN_WIDTH-(this->getRect().x+this->getRect().w);//xMove is updated so as to stick to the wall
        this->wallCollided=true;
    }
    if (a.x<0) // Hit the left wall
    {
        this->xMove=- (this->getRect().x);//Stick to the wall
        this->wallCollided=true;
    }
    if (a.y+a.h>SCREEN_HEIGHT)//Bottom wall. Remember that the y axis is going down
    {
        this->yMove=SCREEN_HEIGHT-(this->getRect().y + this->getRect().h);
        this->wallCollided=true;
    }
    if (a.y<0) //Top wall
    {
        this->yMove=- (this->getRect().y);
        this->wallCollided=true;
    }
    return this->wallCollided;
}

enum kind bloc::getKind()
{
    return(this->myKind);
}

void bloc::setPosition(int x,int y)
{
    this->rect.x=(int)(x-(this->rect.w)/2.);
    this->rect.y=(int)(y-(this->rect.h/2.));
}