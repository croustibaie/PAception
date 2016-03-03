//
// Created by croustibaie on 1/23/16.
//

#ifndef PACEPTION_LEVEL_H
#define PACEPTION_LEVEL_H
#include <vector>
#include <map>
#include"bloc.h"
#include "userInterface.h"

enum gameStatus {PAUSE,PLAY,GAMEOVER};

/* Level's purpose is to control all of the in game action by capturing the inputs and sending the update orders to
 * the blocs*/

class level
{
private:
    std::map<int,bloc*> blocMap;
    userInterface* ui= new userInterface();
    SDL_Texture* backGroundTexture;
    SDL_Renderer* gRenderer;
    /* lastTime and elapsedTime will mesure the time consumed for each frame. This will help adapting speeds*/
    unsigned int lastTime; // In milliseconds
    unsigned int elapsedTime;//In milliseconds

public:
    level();
    level (SDL_Texture* Texture,SDL_Renderer* gRenderer);
    ~level();
    //blocReactions get the reaction of every bloc in the level. The level sends the controller state to every bloc to get the reaction
    void blocReactions();
    //blocDraw goes through every bloc in the level and draws it to the renderer
    void blocDraw();
    //play() is a while procedure in wich inputs are scanned, then blocReactions is called then blocDraw()
    enum gameStatus play ();
    void insertBlocs(bloc* blocArray,int nbBlocs);
    void deleteBloc(int blocID);
    //Collided checks whether the bloc defined by blocID collides with any other one. If so, it calls the blocs' reactions
    bloc* collide (int blocID, SDL_Rect potentialPos);
    // testCollision returns the point of collision between two rectangles. -1,-1 if none
    bool testCollision (SDL_Rect a, SDL_Rect b);
};
#endif //PACEPTION_LEVEL_H
