
//
// Created by croustibaie on 2/10/16.
//

#include "../headers/userInterface.h"

userInterface::userInterface()
{
    if (SDL_NumJoysticks()>0)
    {
        cs = new controllerState*[SDL_NumJoysticks()];
    }
    else
    {
        cs= nullptr;
    }
    for(int i = 0;i<SDL_NumJoysticks();i++)
    {
        cs[i] = new controllerState;

        this->cs[i]->aButton = false;
        this->cs[i]->xButton = false;
        this->cs[i]->yButton = false;
        this->cs[i]->bButton = false;
        this->cs[i]->leftStickVertical = 0;
        this->cs[i]->leftStickHorizontal = 0;
        this->cs[i]->rightStickVertical = 0;
        this->cs[i]->rightStickHorizontal = 0;
        this->cs[i]->startButton = false;
    }
}

bool userInterface::play()
{
    while (SDL_PollEvent(&e)!=0 )
    {
        if( e.type == SDL_QUIT ) //If someone closes the window
        {
            return false;
        }
        else if( e.type == SDL_JOYAXISMOTION )
        {
            motion(e.jaxis.which,e);
        }
    }
    return true;
}

void userInterface::motion(SDL_JoystickID id, SDL_Event e)
{
        //X axis motion
        if (e.jaxis.axis == 0)
        {
            if (abs(e.jaxis.value) > 8000)
            {
                cs[id]->leftStickHorizontal = e.jaxis.value;
            }
            else
            {
                cs[id]->leftStickHorizontal = 0;
            }
            return;
        }
            //Y axis motion
        if (e.jaxis.axis == 1)
        {
            if (abs(e.jaxis.value) > 8000)
            {
                cs[id]->leftStickVertical = e.jaxis.value;
            }
            else
            {
                cs[id]->leftStickVertical = 0;
            }
            return;
        }

    //right stick stuff
        if (e.jaxis.axis == 2)
        {
            if (abs(e.jaxis.value) > 8000)
            {
                cs[id]->rightStickHorizontal = e.jaxis.value;
            }
            else
            {
                cs[id]->rightStickHorizontal = 0;
            }
            return;
        }
        if (e.jaxis.axis == 3)
        {
            if (abs(e.jaxis.value) > 8000)
            {
                cs[id]->rightStickVertical = e.jaxis.value;
            }
            else
            {
                cs[id]->rightStickVertical = 0;
            }
            return;
        }
}

userInterface::~userInterface()
{
    std::cout<<"ui deleted"<<std::endl;

    delete[] cs;
}

struct controllerState** userInterface::getCS()
{
    return cs;
}
