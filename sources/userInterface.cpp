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
    this->cs->leftStickDown=false;
    this->cs->leftStickLeft=false;
    this->cs->leftStickUp=false;
    this->cs->leftStickRight=false;
    this->cs->rightStickDown=false;
    this->cs->rightStickLeft=false;
    this->cs->rightStickUp=false;
    this->cs->rightStickRight=false;
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
                    if( e.jaxis.value < -8000 )
                    {
                        cs->leftStickLeft=true;
                    }
                    else if( e.jaxis.value > 8000 )
                    {
                        cs->leftStickRight=true;
                    }
                    else
                    {
                        cs->leftStickLeft=false;
                        cs->leftStickRight =false;
                    }
                }
                    //Y axis motion
                else if( e.jaxis.axis == 1 )
                {
                    if( e.jaxis.value < -8000 )
                    {
                        cs->leftStickDown=true;
                    }
                    else if( e.jaxis.value > 8000 )
                    {
                        cs->leftStickUp=true;
                    }
                    else
                    {
                        cs->leftStickDown=false;
                        cs->leftStickUp=false;
                    }
                }
            }
        }
    }
    return true;
}