//
// Created by croustibaie on 1/23/16.
//

#ifndef PACEPTION_LEVEL_H
#define PACEPTION_LEVEL_H


#include <vector>
#include <map>
#include "bloc.h"
#include "userInterface.h"

enum gameStatus {PAUSE,PLAY,GAMEOVER};
const bool TEST =true;
// true if you want to run a test without the menu
/* Level's purpose is to control all of the in game action by capturing the inputs and sending the update orders to
 * the blocs*/

class level
{
private:
    std::map<int,bloc*> PlayerblocMap;
    std::map<int,bloc*> SolidblocMap;
    std::map<int,bloc*> NonSolidblocMap;
    userInterface* ui= new userInterface();
    SDL_Texture* backGroundTexture;
    SDL_Texture* pauseTexture;
    SDL_Texture* playAgainTexture;
    SDL_Texture* playAgainTextureSelected;
    SDL_Texture* quitTexture;
    SDL_Texture* quitTextureSelected;
    SDL_Rect pauseRect;
    SDL_Rect playAgainRect;
    SDL_Rect quitRect;
    SDL_Renderer* gRenderer;
    /* lastTime and elapsedTime will mesure the time consumed for each frame. This will help adapting speeds*/
    unsigned int lastTime; // In milliseconds
    unsigned int elapsedTime;//In milliseconds
    unsigned int inputTimer; //Timer to regulate inputs while choosing replay or not
    int numPlayer;// Number of players
    bool replay; // Boolean telling whether the player want to keep playing on this map
    bloc* mapCollide(int blocID, SDL_Rect potentialPos, std::vector<bloc*> ignoredBlocs,std::map<int,bloc*> map);
    void mapReactions(std::map<int,bloc*> *map);
    bool gamePaused;


public:
    level();
    level (SDL_Renderer* gRenderer,int numPlayer);
    ~level();
    //blocReactions get the reaction of every bloc in the level. The level sends the controller state to every bloc to get the reaction
    void blocReactions();
    //blocDraw goes through every bloc in the level and draws it to the renderer
    void blocDraw();
    //play() is a while procedure in which inputs are scanned, then blocReactions is called then blocDraw()
    bool play();// True if players want to play again
    void insertBloc(bloc* blocArray);
    void deleteBloc(int blocID, enum kind blocKind);
    //Collided checks whether the bloc defined by blocID collides with any other one. If so, it calls the blocs' reactions
    bloc* collide(int blocID, SDL_Rect potentialPos, std::vector<bloc*> ignoredBlocs);
    // testCollision returns the point of collision between two rectangles. -1,-1 if none
    bool testCollision(SDL_Rect a, SDL_Rect b);
    SDL_Renderer** getRenderer();
    int getNum();
    bool win();
    bool playAgain();
    void drawPlayAgain();
    bool playAgainHandleInputs(struct controllerState** cs, int playerID);
};
#endif //PACEPTION_LEVEL_H
