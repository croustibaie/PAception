//
// Created by emilien on 11/03/16.
//

#ifndef PACEPTION_BUMPBLOC_H
#define PACEPTION_BUMPBLOC_H

class level;
class playerBloc;
#include "bloc.h"
#include <map>
#define BUMPTIME 500
#define BUMPSPEED 6
class bumpBloc: public bloc {
private :
    float dx;// bloc's actual x direction
    float dy;// bloc's y direction
    float acceleration; // acceleration of the bloc should be always set negative
    float evolvingspeed; // non integer speed to alllow acceleration
public:
    bumpBloc();
    bumpBloc(SDL_Renderer** gRenderer,SDL_Texture* itexture,level* l,int x,int y,float dx, float dy);
    ~bumpBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
     std::map<bloc*,unsigned int> bumpedbloc; // contains all the blocs that have been bumped and the time when it happened
     void setDirection(float dx, float dy);
    float getdx();
    float getdy();
    enum edge bumpingedge; // edge that will bump a bloc

    bool bump(enum edge touchededge,bloc* b); //return true if the bloc b is bumped
};

#endif //PACEPTION_BUMPBLOC_H
