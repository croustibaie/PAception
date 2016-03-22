//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_LEVELCREATOR_H
#define PACEPTION_LEVELCREATOR_H

#define NB_BLOC 60

class level;
class bloc;

#include <fstream>
#include <stdlib.h>
#include <string>
#include <SDL_render.h>

class levelCreator {
private:
    level* l;
    std::string descriptionFile;
    bloc** blocArray;
    int numBloc;
    int playerIndex;
    int pTeam[4];

public:
    levelCreator();
    levelCreator(SDL_Renderer* gRenderer, int pTeam[4]);
    ~levelCreator();
    level* parse();
    void createObject(std::string type,int xpos, int ypos);
    void resetLevel();
};


#endif //PACEPTION_LEVELCREATOR_H
