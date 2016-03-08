//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H

#include "laserBloc.h"
#include "bloc.h"

class playerBloc : public bloc{

private:
    int playerID;
    unsigned int lastShotTimer;
    unsigned int currentTimer;
    laserBloc* laser[20];
    int nextLaser;

public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l, int playerID, int x, int y);
    ~playerBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);//Player bloc's reaction is to do a tryMove and check whether he's dead (false) or not (true)
    void collisionReaction(bloc* b);

};


#endif //PACEPTION_PLAYERBLOC_H
