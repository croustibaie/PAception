//
// Created by gael on 09/03/16.
//

#ifndef PACEPTION_PULSEBLOC_H
#define PACEPTION_PULSEBLOC_H

#define NB_LASERS2 16

#include "bloc.h"
#include "laserBloc.h"


class pulseBloc: public bloc {

private:
    unsigned int Timer;//
    laserBloc* laser[NB_LASERS2]; //P
    int nextLaser;

public:
    pulseBloc();
    pulseBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);
    ~pulseBloc();
    bool collisionReaction(bloc *b);
    int compteur ;


    void shoot( struct controllerState **state, int x_init, int y_init);
};


#endif //PACEPTION_PULSEBLOC_H
