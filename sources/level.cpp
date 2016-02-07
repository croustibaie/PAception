//
// Created by croustibaie on 1/23/16.
//

#include "../headers/bloc.h"
#include "../headers/sdlconfig.h"
#include"./../headers/level.h"

level::level()
{
    backGroundTexture=NULL;
    controller=NULL;
    lastTime=SDL_GetTicks();
    elapsedTime=0;
}

level::level (bloc* array,int numBlocs,SDL_Texture* Texture,SDL_Renderer* gRenderer)
{
    blocArray.reserve(numBlocs);

    for (int i=0 ; i<numBlocs;i++)
    {
        blocArray.push_back(&array[i]);
    }
    this->numBlocs=numBlocs;
    this->backGroundTexture= Texture;
    this->gRenderer=gRenderer;
    this->controller->aButton=false;
    this->controller->xButton=false;
    this->controller->yButton=false;
    this->controller->bButton=false;
    this->controller->leftStickDown=false;
    this->controller->leftStickLeft=false;
    this->controller->leftStickUp=false;
    this->controller->leftStickRight=false;
    this->controller->rightStickDown=false;
    this->controller->rightStickLeft=false;
    this->controller->rightStickUp=false;
    this->controller->rightStickRight=false;
    this->controller->startButton=false;
}

level::~level()
{
    delete controller;
}

/* returns false with a quit command was sent and true if the event queue is null*/


void level::blocReactions()
{
    for (unsigned int i=0; i<numBlocs;i++)
    {
        blocArray.at(i)->react(controller,elapsedTime);
    }
}

void level::blocDraw()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    for (int i=0; i<numBlocs; i++)
    {
        blocArray.at(i)->draw();
    }
    SDL_RenderPresent(gRenderer);
}
enum gameStatus level::play ()
{
    lastTime=SDL_GetTicks();
    elapsedTime=20; // We have to initialize the elapsed time for the very first frame, chose 20ms by default
    while (scanInputs()==true)
    {
        blocReactions();
        unsigned tmptime= SDL_GetTicks(); //Get the number of milliseconds since the game started
        blocDraw();
        elapsedTime= tmptime-lastTime;
        lastTime=tmptime;
        //printf("elapsed time:%u \n", elapsedTime);
    }

    return PLAY;
}

bool level::scanInputs ()
{
    while (SDL_PollEvent(&e)!=0 )
    {
        if( e.type == SDL_QUIT )
        {
            return false;
        }
        else if( e.type == SDL_JOYAXISMOTION )
        {
            //Motion on controller 0
            if( e.jaxis.which == 0 )
            {
                //X axis motion
                if( e.jaxis.axis == 0 )
                {
                    if( e.jaxis.value < -8000 )
                    {
                        controller->leftStickLeft=true;
                    }
                    else if( e.jaxis.value > 8000 )
                    {
                        controller->leftStickRight=true;
                    }
                    else
                    {
                        controller->leftStickLeft=false;
                        controller->leftStickRight =false;
                    }
                }
                    //Y axis motion
                else if( e.jaxis.axis == 1 )
                {
                    if( e.jaxis.value < -8000 )
                    {
                        controller->leftStickDown=true;
                    }
                    else if( e.jaxis.value > 8000 )
                    {
                        controller->leftStickUp=true;
                    }
                    else
                    {
                        controller->leftStickDown=false;
                        controller->leftStickUp=false;
                    }
                }
            }
        }
    }
    return true;
}