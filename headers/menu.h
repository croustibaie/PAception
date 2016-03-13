//
// Created by croustibaie on 3/12/16.
//

#ifndef PACEPTION_MENU_H
#define PACEPTION_MENU_H
class level;
class userInterface;

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
    int currentSelection;

public:
    void playMenu();

};


#endif //PACEPTION_MENU_H
