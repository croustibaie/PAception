//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_MENU_H
#define PACEPTION_MENU_H
#include<string>
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
    SDL_Texture* nbPlayerBackgroundTexture;
    SDL_Texture* xboxControllerTexture;
    SDL_Rect playRect;
    SDL_Rect quitRect;
    SDL_Rect xboxRect[5];
    userInterface* ui;
    levelCreator* lc;
    SDL_Renderer* gRenderer;
    int currentSelection;
    int pTeam[4];
    bool pConfirm[4];
    std::string map;

public:
    menu(SDL_Renderer* gRenderer);
    ~menu();

    void playMenu();
    void teamSelectionMenu();
    void mapSelectionMenu();
    bool playMenuHandleInputs(controllerState** cs, int playerNo);
    bool teamSelectionHandleInputs(controllerState** cs, int playerNo);
    void drawPlayMenu();
    void drawTeamSelectionMenu();
    void drawMapSelectionMenu();

};


#endif //PACEPTION_MENU_H
