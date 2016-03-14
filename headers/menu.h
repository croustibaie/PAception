//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_MENU_H
#define PACEPTION_MENU_H

#include "sdlconfig.h"
class level;
class userInterface;
class levelCreator;


class menu {

private:
    level* l;
    SDL_Texture* backGroundTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* playButtonTextureSelected;
    SDL_Texture* quitButtonTexture;
    SDL_Texture* quitButtonTextureSelected;
    SDL_Rect playRect;
    SDL_Rect quitRect;
    userInterface* ui;
    levelCreator* lc;
    SDL_Renderer* gRenderer;
    int currentSelection;

public:
    menu(SDL_Renderer* gRenderer);
    ~menu();

    void playMenu();
    bool handleInputs(controllerState** cs);
    void drawMenu();

};


#endif //PACEPTION_MENU_H
