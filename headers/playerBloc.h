//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H

#include "laserBloc.h"
#include "bloc.h"

class playerBloc : public bloc{

private:
    int playerID;// Who does this bloc belong to
    unsigned int lastShotTimer;//Timer recording when was the last shot. Used to limit the fire rate
    laserBloc* laser[3]; //Pool of player's lasers.
    int nextLaser; //Number of the nextLaser that should be shot (shoot uses laser[nextLaser])

public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l, int playerID, int x, int y);
    ~playerBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);//Player bloc's reaction is to do a tryMove and check whether he's dead (false) or not (true)
    bool collisionReaction(bloc* b);// Player's reaction to a collision with a bloc b

    void shoot(struct controllerState** state);
};


#endif //PACEPTION_PLAYERBLOC_H
