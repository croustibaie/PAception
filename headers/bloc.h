//
// Created by croustibaie on 12/14/15.
//

#ifndef PA_BLOC_H
#define PA_BLOC_H

class level;
#include <iostream>
#include <vector>
#include <SDL_surface.h>
#include "sdlconfig.h"


enum edge {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
};
class bloc {

protected:
    SDL_Rect rect;// Bloc's hitbox
    SDL_Texture *texture;//Bloc's sprite
    SDL_Renderer* gRenderer;
    level* l;
    int speed;//speed is used a multiplicative coeff. to compute xMove and yMove
    unsigned int blocId; //Bloc's unique ID, is it really useful?
    int xMove; // The x movement that the bloc is willing to perform, level will check for collision and this value will be adapted
    int yMove;// Same as xMove
    static unsigned int nextBlocId;

    bool shield ; // use only for player bloc
    bool killOnTouch; //Does the bloc kill players?
    bool killOnTouch; //Does the bloc kill 0players?
    bool isBumped; // Is the bloc bumped ?
    bool reflect; //Does the bloc reflect lasers ?
    enum kind myKind; // Kind can be LASER,PLAYER or STATIC so far. Useful to determine a generic bloc's type
    bool wallCollided; //Return true if the bloc collided with a wall and it hasn't been resolved yet
    std::vector<bloc*> ignoredBlocs;
public:
    /* Move the bloc of x pixels in horizontal and y in vertical */


    bloc (); //Default constructor, should never be used

    bloc (SDL_Renderer** gRenderer,const char* path,level* l,int x,int y);// Correct constructor

    ~bloc(); // Destructor

    virtual bool react(struct controllerState** state,unsigned int elapsedTime); //Bloc's reactions to given inputs, returns false if the bloc asked to be killed
    virtual void draw(); // The bloc draws itself to the renderer
    void move(int x , int y); // The bloc applies the movement, this should be done after having checked that there are no collisions
    bool tryMove(int x, int y);//The bloc changes xMove and yMove and then asks level for collisions.Returns false if the bloc asked to be killed, true otherwise.
    virtual bool collisionReaction(bloc* b);//Bloc's reaction to a collision with another bloc. Returns false if it dies
    virtual bool wallCollision(SDL_Rect a); // Checks if the bloc collides a border, if yes, stop it in one direction calls tryMove for the movement in another direction and returns whether it collided, do nothing otherwise
    void setSpeed(int speed);

    SDL_Rect getRect() const;
    int getSpeed() const;
    int getxMove() const;
    int getyMove() const;
    int getBlocId() const;
    SDL_Renderer* getRenderer() const;
    SDL_Texture* getTexture() const;
    bool kill();//Does the bloc have the killontouch attribute set to true or false.
    bool getBumped();
    void setBumped(bool Bumped);
    enum kind getKind();
    void setPosition(int x, int y);
    bool isReflector();//Does the bloc reflect ?
    std::vector<bloc*> getIgnoredBlocs();

    virtual void setDirection(float dx,float dy);
    virtual float getdx();
    virtual float getdy();
    // about the bumping

    virtual bool bump(enum edge touchededge, bloc* b);
    // NB : Any bloc that is killed must be killed in his own collisionReaction
    bool shieldState();
};

#endif