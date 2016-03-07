//
// Created by croustibaie on 3/3/16.
//

#ifndef PACEPTION_LASERBLOC_H
#define PACEPTION_LASERBLOC_H
#include "./bloc.h"
#include "./level.h"
#include <math.h>
#include "./sdlconfig.h"

class laserBloc : public bloc {
private:
    float dx;
    float dy;
    int xMove;
    int yMove;

    public:
    laserBloc();
    laserBloc(SDL_Renderer** gRenderer,const char* path,level* l, int x,int y,int dx,int dy);
    ~laserBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool tryMove(int x, int y);
    void collisionReaction(bloc* b);

};


#endif //PACEPTION_LASERBLOC_H
