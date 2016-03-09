//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H
#define MAX_AMMO 10
#define NB_LASERS 30
#define PLAYER_HP 3
#define INITIALSPEED 8
#include "laserBloc.h"
#include "bloc.h"

class playerBloc : public bloc{

private:
    int playerID;// Who does this bloc belong to
    unsigned int lastShotTimer;//Timer recording when was the last shot. Used to limit the fire rate

    laserBloc* laser[NB_LASERS]; //Pool of player's lasers.
    int ammo;
    int nextLaser; //Number of the nextLaser that should be shot (shoot uses laser[nextLaser])
    int hp; //Player's health points
    unsigned int reloadTimer;
public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l, int playerID, int x, int y);
    ~playerBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);//Player bloc's reaction is to do a tryMove and check whether he's dead (false) or not (true)
    bool collisionReaction(bloc* b);// Player's reaction to a collision with a bloc b

    void shoot(struct controllerState** state);
};


#endif //PACEPTION_PLAYERBLOC_H
