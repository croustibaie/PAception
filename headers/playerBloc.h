//
// Created by croustibaie on 3/1/16.
//

#ifndef PACEPTION_PLAYERBLOC_H
#define PACEPTION_PLAYERBLOC_H

#include "./bloc.h"

class playerBloc : public bloc{

private: int playerID;

public:
    playerBloc();
    playerBloc(SDL_Renderer** gRenderer,const char* path,level* l, int playerID);
    ~playerBloc();
    void react(struct controllerState** state,unsigned int elapsedTime);
    void tryMove(int x, int y);


};


#endif //PACEPTION_PLAYERBLOC_H
