//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_LEVELCREATOR_H
#define PACEPTION_LEVELCREATOR_H
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
    int numPlayers;
    bloc** blocArray;
    int numBloc;

public:
    levelCreator();
    levelCreator(SDL_Renderer* gRenderer);
    ~levelCreator();
    level* parse();
    void createObject(std::string type,int xpos, int ypos);
};


#endif //PACEPTION_LEVELCREATOR_H
