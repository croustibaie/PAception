//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_STATICBLOC_H
#define PACEPTION_STATICBLOC_H

#include "bloc.h"

class staticBloc: public bloc {

public:
    staticBloc();
    staticBloc(SDL_Renderer** gRenderer,SDL_Texture* itexture,level* l,int x,int y);
    ~staticBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
};


#endif //PACEPTION_STATICBLOC_H
