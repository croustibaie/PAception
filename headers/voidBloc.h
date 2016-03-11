//
// Created by benoit on 10/03/16.
//

#ifndef PACEPTION_VOIDBLOC_H_H
#define PACEPTION_VOIDBLOC_H_H
#include "bloc.h"
#include <map>
#define EPS 4

class voidBloc: public bloc {

public:
    voidBloc();
    voidBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);
    ~voidBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
};

#endif //PACEPTION_VOIDBLOC_H_H
