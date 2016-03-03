//
// Created by croustibaie on 12/14/15.
//

#include<SDL.h>
#include "../headers/sdlconfig.h"
#include "../headers/level.h"


unsigned int bloc::nextBlocId=0;

bloc::bloc ()
{
    this->rect.x=0;
    this->rect.y =0;
    this->rect.w=10;
    this->rect.h=10;
    this->speed=8;
    texture=NULL;
    gRenderer=NULL;
    killOnTouch=false;
    this->blocId=nextBlocId;
    nextBlocId++;
}

bloc::bloc (SDL_Renderer** gRender,const char* path, level* l)
{
    this->l=l;
    if (*gRender==NULL)
    {
        std::cout<< "In bloc constructor, no render"<<std::endl;
    }
    this->rect.x=0;
    this->rect.y=0;
    this->rect.w=50;
    this->rect.h=50;
    texture=NULL;
    this->speed=16;
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

bloc::bloc(const bloc& b)
{
    this->gRenderer=b.getRenderer();
    loadMedia(&texture,&gRenderer,"/home/croustibaie/Documents/PAception/red.bmp");
    // this->texture=b.getTexture();
    this->rect=b.getRect();
    this->speed=b.getSpeed();
    this->blocId=b.getBlocId();
}

bloc::~bloc()
{
    if (texture!=NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void bloc::react(struct controllerState* state,unsigned int elapsedTime)
{
    int correctedSpeed= (int)(round((float)(speed)*(float)elapsedTime/20)); //We have to adapt the initial speed to the frame duration
    tryMove((int)(correctedSpeed*(float)(state->leftStickHorizontal)/32000),(int)(correctedSpeed*(float)(state->leftStickVertical)/32000) );
}

void bloc::draw()
{
    if (texture==NULL)
    {
        std::cout<<"no texture"<<std::endl;
    }
    SDL_RenderCopy(gRenderer,texture, NULL, &rect );
}

void bloc::tryMove(int x, int y)
{
    SDL_Rect a= this->getRect();
    a.x+=x;
    a.y+=y;

    int xmove=x;
    int ymove=y;

    if (this->l->collide(this->blocId,a)!= nullptr) //If there is a collision
    {
        this->move(0,0); //TODO: bloc's collision reaction should be there
    }
    else //Here we check that we're not trying to go out of the window
    {
        if (a.x+a.w>SCREEN_WIDTH)
        {
            xmove=SCREEN_WIDTH-(this->getRect().x+this->getRect().w);
        }
        if (a.x<0)
        {
            xmove=- (this->getRect().x);
        }
        if (a.y+a.h>SCREEN_HEIGHT)
        {
            ymove=SCREEN_HEIGHT-(this->getRect().y + this->getRect().h);
        }
        if (a.y<0)
        {
            ymove=- (this->getRect().y);
        }
        move(xmove,ymove);
    }
}

void bloc::move(int x , int y)
{
    this->rect.x+=x;
    this->rect.y+=y;
}

void bloc::setSpeed(int speed)
{
    this->speed=speed;
}

int bloc::getBlocId() const
{
    return blocId;
}

 SDL_Renderer* bloc::getRenderer() const
{
    return gRenderer;
}

SDL_Texture* bloc::getTexture() const
{
    return texture;
}

SDL_Rect bloc::getRect() const
{
    return rect;
}

int bloc::getSpeed() const
{
    return speed;
}

void bloc::collisionReaction(bloc *b)
{
    tryMove(0,0);
}

bool bloc::kill()
{
    return killOnTouch;
}