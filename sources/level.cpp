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
    blocArray= array;
    this->numBlocs=numBlocs;
    backGroundTexture= Texture;
    this->gRenderer=gRenderer;
    this->controller->aButton=false;
    controller->xButton=false;
    controller->yButton=false;
    controller->bButton=false;
    controller->leftStickDown=false;
    controller->leftStickLeft=false;
    controller->leftStickUp=false;
    controller->leftStickRight=false;
    controller->rightStickDown=false;
    controller->rightStickLeft=false;
    controller->rightStickUp=false;
    controller->rightStickRight=false;
    controller->startButton=false;
}

level::~level()
{
}

/* returns false with a quit command was sent and true if the event queue is null*/


void level::blocReactions()
{
    for (int i=0; i<numBlocs;i++)
    {
        blocArray[i].react(controller,elapsedTime);
    }
}

void level::blocDraw()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    for (int i=0; i<numBlocs; i++)
    {
        blocArray[i].draw();
    }
    SDL_RenderPresent(gRenderer);
}
enum gameStatus level::play ()
{
    lastTime=SDL_GetTicks();
    while (scanInputs()==true)
    {
        blocReactions();
        unsigned tmptime= SDL_GetTicks();
        blocDraw();
        elapsedTime= tmptime-lastTime;
        lastTime=tmptime;
        printf("elapsed time:%u \n", elapsedTime);
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