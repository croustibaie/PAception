//
// Created by benoit on 10/03/16.
//

#ifndef PACEPTION_DIAMONDBLOC_H
#define PACEPTION_DIAMONDBLOC_H

#include "bloc.h"
#include "laserBloc.h"
#include <map>

#define NB_LASERS3 40
#define EPS_SEC 20 // small distance to add so that the laser issued by the bloc are
                  // issued from the exterior of the hitbox of the code

class diamondBloc: public bloc {

private:
    laserBloc* laser[NB_LASERS3]; //Pool of player's lasers.
    int nextLaser; // Number of next laser that should be shot
    int laser_counter; // defines the vertex of the cube from which the refracted laser
                       // will be issued
public:
    diamondBloc();
    diamondBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    ~diamondBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
    void shoot(int x , int y);
};


#endif //PACEPTION_DIAMONDBLOC_H
