//
// Created by emilien on 09/03/16.
//

#ifndef PACEPTION_FREEZEBLOC_H_H
#define PACEPTION_FREEZEBLOC_H_H
#include "bloc.h"
#include <map>
#define FREEZETIME 3000
 // time during which a bloc is slowed in ms
class freezeBloc: public bloc {

public:
    freezeBloc();
    freezeBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    ~freezeBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
     std::map<bloc*,unsigned int> frozenbloc; // contains all the blocs that have been frozen and the time when it happened
};

#endif //PACEPTION_FREEZEBLOC_H_H
