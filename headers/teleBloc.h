//
// Created by gael on 14/03/16.
//



#ifndef PACEPTION_TELEBLOC_H
#define PACEPTION_TELEBLOC_H


#define EPS2 500
#define TELETIME 3000

class teleBloc: public bloc {

private:
    teleBloc *t;
    int x_tele; // là où on se téléporte
    int y_tele;
    bool active;
    int compteur;
    int timerTele;
public:

    teleBloc();

    teleBloc(SDL_Renderer **gRenderer,SDL_Texture* itexture, level *l, int x, int y);

    void setTeleBloc(teleBloc *t2);

    ~teleBloc();

    bool react(struct controllerState **state, unsigned int elapsedTime);

    bool collisionReaction(bloc *b);

    void setBool(bool b);

    void setSibling(teleBloc *t);
};

#endif
