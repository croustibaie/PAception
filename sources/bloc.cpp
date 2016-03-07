//
// Created by croustibaie on 12/14/15.
//

#include<SDL.h>
#include "../headers/sdlconfig.h"
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
}

// Copy constructor

bloc::bloc(const bloc& b)
{
    this->gRenderer=b.getRenderer();
    loadMedia(&texture,&gRenderer,"./red.bmp");
    // this->texture=b.getTexture();
    this->rect=b.getRect();
    this->speed=b.getSpeed();
    this->blocId=b.getBlocId();
}

// Destructor

bloc::~bloc()
{
}

bool bloc::react(struct controllerState** state,unsigned int elapsedTime)
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
        if (a.x+a.w>SCREEN_WIDTH) //TODO : think about a strict or large inequality
        {
            xmove=SCREEN_WIDTH-(this->getRect().x+this->getRect().w);
        }
        if (a.x<0)
        {
            xmove=- (this->getRect().x);
        }
        if (a.y+a.h>SCREEN_HEIGHT) //TODO: Same as previously
        {
            ymove=SCREEN_HEIGHT-(this->getRect().y + this->getRect().h);
        }
        if (a.y<0)
        {
            ymove=- (this->getRect().y);
        }
        move(xmove,ymove);
    }
    return true;
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

void bloc::collisionReaction(bloc *b)
{
    tryMove(0,0);
}

// Kill bloc

bool bloc::kill()
{
    return killOnTouch;
}