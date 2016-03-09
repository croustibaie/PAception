//
// Created by gael on 09/03/16.
//

#ifndef PACEPTION_PULSEBLOC_H
#define PACEPTION_PULSEBLOC_H

#include "bloc.h"

class pulseBloc: public bloc {

public:
    pulseBloc();
    pulseBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);
    ~pulseBloc();
    bool collisionReaction(bloc *b);
    int compteur ;
};


#endif //PACEPTION_PULSEBLOC_H
