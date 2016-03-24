//
// Created by emilien on 24/03/16.
//

#ifndef PACEPTION_LIFEBLOC_H
#define PACEPTION_LIFEBLOC_H

#include "bloc.h"
#define HPSTOCK 2
#define HPTIME 20000
class lifeBloc: public bloc {
private:
    unsigned int lifetimer;
public:
    lifeBloc();
    lifeBloc(SDL_Renderer** gRenderer,SDL_Texture* texture,level* l,int x,int y);
    ~lifeBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);

};
#endif //PACEPTION_LIFEBLOC_H
