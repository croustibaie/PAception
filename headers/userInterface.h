//
// Created by croustibaie on 2/10/16.
//

#ifndef PACEPTION_USERINTEFACE_H
#define PACEPTION_USERINTEFACE_H


#include "sdlconfig.h"

class userInterface {
private:
    struct controllerState **cs = NULL ; //Array of controllerStates, contains the controllers' states
    SDL_Event e;

public:
    userInterface(); //Destructor automatically detects the number of controllers
    ~userInterface();

    bool play();  // Goes through the SDL_Event e and updates the controllerStates

    struct controllerState** getCS(); //Returns cs


    void motion(SDL_JoystickID id, SDL_Event e); //Method to update the controllerStates when the even is a JoyAxisMotion
};


#endif //PACEPTION_USERINTEFACE_H
