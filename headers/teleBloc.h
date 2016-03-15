//
// Created by gael on 14/03/16.
//



#ifndef PACEPTION_TELEBLOC_H
#define PACEPTION_TELEBLOC_H

#endif //PACEPTION_TELEBLOC_H

#define EPS2 100
#define TELETIME 3000

class teleBloc: public bloc {

public:
    teleBloc* t;
    int x_tele; // là où on se téléporte
    int y_tele;
    bool BOOLEAN;
    teleBloc();
    teleBloc(SDL_Renderer** gRenderer,level* l,int x,int y);
    void setteleBloc(teleBloc* t2);

    ~teleBloc();
    bool react(struct controllerState** state,unsigned int elapsedTime);
    bool collisionReaction(bloc* b);
};
