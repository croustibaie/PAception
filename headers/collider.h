//
// Created by croustibaie on 2/2/16.
//

#ifndef PACEPTION_COLLIDER_H
#define PACEPTION_COLLIDER_H
#include "bloc.h"

class collider {
private:
    bloc* blocArray;

public:
    void collide (bloc movingBloc, bloc staticBloc, int xDir, int yDir);
    void triggerHits (bloc movingBloc, bloc staticBloc, int xDir, int yDir);
    void addBloc(bloc newBloc);
    void removeBloc(bloc newBloc);
};


#endif //PACEPTION_COLLIDER_H
