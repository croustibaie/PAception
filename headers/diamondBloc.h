//
// Created by benoit on 10/03/16.
//

class laserBloc;

#ifndef PACEPTION_DIAMONDBLOC_H
#define PACEPTION_DIAMONDBLOC_H
#include "bloc.h"
#include <map>
#define NB_LASERS 40

class diamondBloc: public bloc {

private:
    laserBloc* laser[NB_LASERS]; //Pool of player's lasers.
    int nextLaser; // Number of next laser that should be shot
    int laser_counter; // defines the vertex of the cube from which the refracted laser
                       // will be issued
public:
    diamondBloc();
    diamondBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);
    ~diamondBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
    void shoot(int x , int y);
};


#endif //PACEPTION_DIAMONDBLOC_H
