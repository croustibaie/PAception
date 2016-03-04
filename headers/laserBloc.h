//
// Created by croustibaie on 3/3/16.
//

#ifndef PACEPTION_LASERBLOC_H
#define PACEPTION_LASERBLOC_H
#include "./bloc.h"

class laserBloc : public bloc {
private:
    int dx;
    int dy;
public:
    laserBloc();
    laserBloc(SDL_Renderer** gRenderer,const char* path,level* l, int x,int y,int dx,int dy);
    ~laserBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);


};


#endif //PACEPTION_LASERBLOC_H
