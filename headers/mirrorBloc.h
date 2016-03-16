//
// Created by geabitbol on 14/03/16.
//

#ifndef PACEPTION_MIRRORBLOC_H
#define PACEPTION_MIRRORBLOC_H

#include "bloc.h"

class mirrorBloc: public bloc {

public:
    mirrorBloc();
    mirrorBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    ~mirrorBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
};


#endif //PACEPTION_MIRRORBLOC_H
