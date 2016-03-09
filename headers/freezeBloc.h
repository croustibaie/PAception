//
// Created by emilien on 09/03/16.
//

#ifndef PACEPTION_FREEZEBLOC_H_H
#define PACEPTION_FREEZEBLOC_H_H
#include "bloc.h"

class freezeBloc: public bloc {

public:
    freezeBloc();
    freezeBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);
    ~freezeBloc();
    bool react(struct controllerState* state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
};

#endif //PACEPTION_FREEZEBLOC_H_H
