//
// Created by croustibaie on 3/3/16.
//

#ifndef PACEPTION_LASERBLOC_H
#define PACEPTION_LASERBLOC_H
class level;

#include <math.h>
#include "bloc.h"

class laserBloc : public bloc {
private:
    float dx;// Laser's actual x direction
    float dy;// Laser's y direction

    public:
    laserBloc();//Default constructor, should never be used
    laserBloc(SDL_Renderer** gRenderer,const char* path,level* l, int x,int y,int dx,int dy);//Correct constructor
    ~laserBloc();//destructor
    bool react(struct controllerState** state,unsigned int elapsedTime);//Laser's reaction to user inputs
    bool collisionReaction(bloc* b);//Laser's reaction to a collision with a bloc b
    bool wallCollision(SDL_Rect a);
    void setDirection(float dx, float dy);
};


#endif //PACEPTION_LASERBLOC_H
