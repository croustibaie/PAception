//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H
#define MAX_AMMO 20
#define NB_LASERS 30
#define PLAYER_HP 10
#define INITIALSPEED 8
#define SHIELD_MAX 3000
#include "laserBloc.h"
#include "bloc.h"

class playerBloc : public bloc{

private:
    int playerID;// Who does this bloc belong to
    unsigned int lastShotTimer;//Timer recording when was the last shot. Used to limit the fire rate
    int teamNumber;
    laserBloc laser[NB_LASERS]; //Pool of player's lasers.
    int ammo;
    int nextLaser; //Number of the nextLaser that should be shot (shoot uses laser[nextLaser])
    int hp; //Player's health points
    int pPos; // Player's position around the table
    /*                            2
     *                   ____________________
     *                   |                  |
     *              1    |                  |  3
     *                   |__________________|
     *                            0
    */
     unsigned int reloadTimer;
    int shieldTimer;
    unsigned int lastShieldTimer;
   // SDL_Rect rectBase[MAX_AMMO+PLAYER_HP+2]; //size and number of the health point rectangles
    SDL_Texture *shieldTexture;
    SDL_Texture *hpTexture; // color of health point bar
    SDL_Texture *heartTexture; //Indicator of health point
    SDL_Texture *ammoTexture; // color of ammunition bar
    SDL_Texture *bulletTexture; // Indicator of ammunition
    float dx;// current x direction if not bumped x direction of bumping otherwise
    float dy;// current y direction if not bumped y direction of bumping otherwise
public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,SDL_Texture* itexture, SDL_Texture* laserTexture,SDL_Texture* shieldTexture,level* l, int playerID,int teamId,int pPos, int x, int y);
    ~playerBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);//Player bloc's reaction is to do a tryMove and check whether he's dead (false) or not (true)
    bool collisionReaction(bloc* b);// Player's reaction to a collision with a bloc b
    void draw();
    void shoot(struct controllerState** state);
    void setDirection(float dx, float dy);
    float getdx();
    float getdy();
    int getTeamNumber();
    void addHp(int hp); // method to add some healthpoints
};


#endif //PACEPTION_PLAYERBLOC_H
