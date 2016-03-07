//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H

#include "./bloc.h"

class playerBloc : public bloc{

private:
    int playerID;
    enum kind myKind;

public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l, int playerID, int x, int y);
    ~playerBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);//Player bloc's reaction is to do a tryMove and check whether he's dead (false) or not (true)
    bool tryMove(int x, int y); //Classic tryMove, level will check for any collision (true no destruction) (false destruction)
    void collisionReaction(bloc* b);

};


#endif //PACEPTION_PLAYERBLOC_H
