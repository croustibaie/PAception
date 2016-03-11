//
// Created by emilien on 11/03/16.
//

#ifndef PACEPTION_BUMPBLOC_H
#define PACEPTION_BUMPBLOC_H

class level;
#include "bloc.h"
#include <map>
enum edge {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
};
class bumpBloc: public bloc {
private :
    float dx;// bloc's actual x direction
    float dy;// bloc's y direction
public:
    bumpBloc();
    bumpBloc(SDL_Renderer** gRenderer,const char* path,level* l,int x,int y,int dx, int dy);
    ~bumpBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
     std::map<bloc*,unsigned int> bumpedbloc; // contains all the blocs that have been bumped and the time when it happened
     void setDirection(float dx, float dy);
    enum edge bumpededge;
};

#endif //PACEPTION_BUMPBLOC_H
