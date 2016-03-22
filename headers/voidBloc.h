//
// Created by benoit on 10/03/16.
//

#ifndef PACEPTION_VOIDBLOC_H_H
#define PACEPTION_VOIDBLOC_H_H
#include "bloc.h"
#include <map>
#define KILLZONE 40

class voidBloc: public bloc {
private:
    double angle;
public:
    voidBloc();
    voidBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    ~voidBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
    void draw();
};

#endif //PACEPTION_VOIDBLOC_H_H
