//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_MENU_H
#define PACEPTION_MENU_H
class level;
class userInterface;
class levelCreator;
#include<string>
#include "sdlconfig.h"
#define NB_MAP 3

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
    SDL_Texture* mapTextures[NB_MAP];
    SDL_Rect playRect;
    SDL_Rect quitRect;
    SDL_Rect xboxRect[5];
    userInterface* ui;
    levelCreator* lc;
    SDL_Renderer* gRenderer;
    int currentSelection;
    int pTeam[4]; //Players' teams
    int pPos[4]; // Players' position around the table
    bool pConfirm[4];
    unsigned int inputTimer;
    std::string maps[NB_MAP];

public:
    menu(SDL_Renderer* gRenderer);
    ~menu();

    void playMenu();
    void teamSelectionMenu();
    void mapSelectionMenu();
    bool playMenuHandleInputs(controllerState** cs, int playerNo);
    bool teamSelectionHandleInputs(controllerState** cs, int playerNo);
    bool mapSelectionHandleInputs(controllerState** cs, int playerNo);
    void drawPlayMenu();
    void drawTeamSelectionMenu();
    void drawMapSelectionMenu();

};


#endif //PACEPTION_MENU_H
