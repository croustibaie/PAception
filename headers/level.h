//
// Created by croustibaie on 1/23/16.
//

#ifndef PACEPTION_LEVEL_H
#define PACEPTION_LEVEL_H
#include <map>

enum gameStatus {PAUSE,PLAY,GAMEOVER};

/* Level's purpose is to control all of the in game action by capturing the inputs and sending the update orders to
 * the blocs*/

class level
{
private:
    bloc* blocArray;
    int numBlocs;
    SDL_Texture* backGroundTexture;
    SDL_Renderer* gRenderer;
    struct controllerState* controller;
    /* lastTime and elapsedTime will mesure the time consumed for each frame. This will help adapting speeds*/
    unsigned int lastTime;
    unsigned int elapsedTime;
    SDL_Event e;

public:
    level();

    level (bloc* array,int numBlocs,SDL_Texture* Texture,SDL_Renderer* gRenderer);
    ~level();

    /* returns false with a quit command was sent and true if the event queue is null*/
    bool scanInputs ();
    void blocReactions();
    void blocDraw();
    enum gameStatus play ();
};
#endif //PACEPTION_LEVEL_H
