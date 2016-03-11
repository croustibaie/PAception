//
// Created by gael on 09/03/16.
//

#ifndef PACEPTION_PULSEBLOC_H
#define PACEPTION_PULSEBLOC_H

#define NB_LASERS2 8

#include "bloc.h"
#include "laserBloc.h"


class pulseBloc: public bloc {

private:
    unsigned int Timer;//
    laserBloc* laser[NB_LASERS2]; //P
    int nextLaser;

public:
    pulseBloc();
    pulseBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    ~pulseBloc();
    bool collisionReaction(bloc *b);
    int compteur ;


    void shoot();
};


#endif //PACEPTION_PULSEBLOC_H
