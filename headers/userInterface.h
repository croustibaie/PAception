//
// Created by croustibaie on 2/10/16.
//

#ifndef PACEPTION_USERINTEFACE_H
#define PACEPTION_USERINTEFACE_H


#include "sdlconfig.h"

class userInterface {
private:
    struct controllerState **cs = NULL ;
    SDL_Event e;

public:
    userInterface();
    ~userInterface()
    {
        std::cout<<"ui deleted"<<std::endl;
    }
    bool play();
    struct controllerState** getCS()
    {
        return cs;
    }

    void motion(SDL_JoystickID id, SDL_Event e);


};


#endif //PACEPTION_USERINTEFACE_H
