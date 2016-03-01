//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H

#include "./bloc.h"

class playerBloc : public bloc{

public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l);
    ~playerBloc();
    void react(struct controllerState* state,unsigned int elapsedTime);


};


#endif //PACEPTION_PLAYERBLOC_H
