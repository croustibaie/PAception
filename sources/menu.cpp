//
// Created by croustibaie on 3/12/16.
//

#include "../headers/menu.h"
#include "../headers/level.h"
#include "../headers/levelCreator.h"
#include "../headers/userInterface.h"

menu::menu(SDL_Renderer *gRenderer)
{
    this->gRenderer=gRenderer;
    loadMedia(&this->backGroundTexture,&gRenderer,"./textures/menuBG.png");
    loadMedia(&this->playButtonTexture,&gRenderer,"./textures/PlayAnimation.gif");
    loadMedia(&this->playButtonTextureSelected,&gRenderer,"./textures/play_button.png");
    loadMedia(&this->quitButtonTexture,&gRenderer,"./textures/Bouton_Quit.jpg");
    loadMedia(&this->quitButtonTextureSelected,&gRenderer,"./textures/ButtonQuitGame.png");
    this->playRect.x=SCREEN_WIDTH/8*3;
    this->playRect.w=SCREEN_WIDTH/6;
    this->playRect.y=SCREEN_HEIGHT/8*3;
    this->playRect.h=SCREEN_HEIGHT/6;
    this->quitRect.x=SCREEN_WIDTH/8*3;
    this->quitRect.w=SCREEN_WIDTH/6;
    this->quitRect.y=SCREEN_HEIGHT/8*5;
    this->quitRect.h=SCREEN_HEIGHT/6;
    this->lc= new levelCreator(gRenderer,1);
    this->l=nullptr;
    this->currentSelection=1;
    this->ui=new userInterface();
}

menu::~menu()
{
    delete(this->ui);
    delete(this->lc);
}




void menu::playMenu()
{
    bool play=false;
    bool quit=false;
    while(ui->play() and (!quit))
    {
        quit=!(handleInputs(ui->getCS()));
        drawMenu();

    }
    if (currentSelection==0)
    {
        this->l=lc->parse();
        std::cout<<"level parsed"<<std::endl;
        this->l->play();

        return;
    }
    else
    {
        return;
    }
}

bool menu::handleInputs(controllerState **cs) //false if made  decision and want to set quit to true
{
    if (cs[0]->aButton)
    {
        currentSelection=0;
        std::cout << "quit is true" << std::endl;
        return false;
    }
    if(cs[0]->leftStickVertical>0)
    {
        std::cout<<"current selection=1"<<std::endl;
        currentSelection= 1;
    }
    else if(cs[0]->leftStickVertical<0)
    {
        std::cout<<"current selection=0"<<std::endl;
        currentSelection=0;
    }
    return true;
}

void menu::drawMenu()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    if (this->currentSelection==0)
    {
        SDL_RenderCopy(gRenderer,playButtonTextureSelected,NULL,&playRect);
    }
    else
    {
        SDL_RenderCopy(gRenderer,playButtonTexture,NULL,&playRect);
    }
    if (this->currentSelection==1)
    {
        SDL_RenderCopy(gRenderer,quitButtonTextureSelected,NULL,&quitRect);
    }
    else
    {
        SDL_RenderCopy(gRenderer,quitButtonTexture,NULL,&quitRect);
    }
    SDL_RenderPresent(gRenderer);
}