//
// Created by croustibaie on 2/10/16.
//

#include "../headers/userInterface.h"

userInterface::userInterface()
{
    this->cs->aButton=false;
    this->cs->xButton=false;
    this->cs->yButton=false;
    this->cs->bButton=false;
    this->cs->leftStickVertical=0;
    this->cs->leftStickHorizontal=0;
    this->cs->rightStickVertical=0;
    this->cs->rightStickHorizontal=0;
    this->cs->startButton=false;
}

bool userInterface::play()
{
    while (SDL_PollEvent(&e)!=0 )
    {
        if( e.type == SDL_QUIT )
        {
            return false;
        }
        else if( e.type == SDL_JOYAXISMOTION )
        {
            //Motion on cs 0
            if( e.jaxis.which == 0 )
            {
                //X axis motion
                if( e.jaxis.axis == 0 )
                {
                    if( abs(e.jaxis.value) > 8000 )
                    {
                        cs->leftStickHorizontal=e.jaxis.value;
                    }
                    else
                    {
                        cs->leftStickHorizontal=0;
                    }
                }
                    //Y axis motion
                else if( e.jaxis.axis == 1 )
                {
                    if( abs(e.jaxis.value) > 8000 )
                    {
                        cs->leftStickVertical=e.jaxis.value;
                    }
                    else
                    {
                        cs->leftStickVertical=0;
                    }
                }
            }
        }
    }
    return true;
}