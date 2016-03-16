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
    loadMedia(&this->playButtonTexture,&gRenderer,"./textures/playbutton.png");
    loadMedia(&this->playButtonTextureSelected,&gRenderer,"./textures/playButtonSelected.png");
    loadMedia(&this->quitButtonTexture,&gRenderer,"./textures/quitButton.png");
    loadMedia(&this->quitButtonTextureSelected,&gRenderer,"./textures/quitButtonSelected.png");
    loadMedia(&this->nbPlayerBackgroundTexture,&gRenderer,"./textures/teamchoose.png");
    loadMedia(&this->xboxControllerTexture,&gRenderer,"./textures/xbox.png");
    this->playRect.x=SCREEN_WIDTH/8*3;
    this->playRect.w=SCREEN_WIDTH/3;
    this->playRect.y=SCREEN_HEIGHT/4;
    this->playRect.h=SCREEN_HEIGHT/3;
    this->quitRect.x=SCREEN_WIDTH/8*3;
    this->quitRect.w=SCREEN_WIDTH/3;
    this->quitRect.y=SCREEN_HEIGHT/2;
    this->quitRect.h=SCREEN_HEIGHT/3;
    this->l=nullptr;
    this->currentSelection=1;
    this->ui=new userInterface();
    this->pTeam[0]=0;
    this->pTeam[1]=0;
    this->pTeam[2]=0;
    this->pTeam[3]=0;
    this->pConfirm[0]=false;
    this->pConfirm[1]=false;
    this->pConfirm[2]=false;
    this->pConfirm[3]=false;
    this->xboxRect[0].x=350;
    this->xboxRect[0].w=40;
    this->xboxRect[0].y=280;
    this->xboxRect[0].h=30;
    this->xboxRect[1].x=150;
    this->xboxRect[1].w=40;
    this->xboxRect[1].y=200;
    this->xboxRect[1].h=30;
    this->xboxRect[2].x=600;
    this->xboxRect[2].w=40;
    this->xboxRect[2].y=200;
    this->xboxRect[2].h=30;
    this->xboxRect[3].x=150;
    this->xboxRect[3].w=40;
    this->xboxRect[3].y=480;
    this->xboxRect[3].h=30;
    this->xboxRect[4].x=600;
    this->xboxRect[4].w=40;
    this->xboxRect[4].y=480;
    this->xboxRect[4].h=30;
}

menu::~menu()
{
    delete(this->ui);
    delete(this->lc);
}




void menu::playMenu()
{
    bool quit=false;
    bool confirm=false;
    while(ui->play() and (!quit))
    {
        confirm=playMenuHandleInputs(ui->getCS(),0);
        drawPlayMenu();
        if (currentSelection==0 && confirm)
        {
            confirm=false;
            teamSelectionMenu();
        }
        if (currentSelection==1 && confirm)
        {
            quit=true;
        }

    }
}

bool menu::playMenuHandleInputs(controllerState **cs, int playerNo) //true if player gave confirmation
{
    if (cs[playerNo]->aButton)
    {
        cs[playerNo]->aButton=false;
        return true;
    }
    if (cs[playerNo]->bButton)
    {
        cs[playerNo]->bButton=false;
        currentSelection=1;
        return true;
    }
    if(cs[playerNo]->leftStickVertical>0)
    {
        currentSelection= 1;
    }
    else if(cs[playerNo]->leftStickVertical<0)
    {
        currentSelection=0;
    }
    return false;
}

bool menu::teamSelectionHandleInputs(controllerState **cs, int playerNo)  //true if player gave confirmation
{
    if (cs[playerNo]->aButton)
    {
        cs[playerNo]->aButton=false; //this is done so that the user can give only one a input at a time
        if (pTeam[playerNo]!=0)
        {
            if (pConfirm[playerNo] == false)
            {
                pConfirm[playerNo] = true;
                std::cout << "confirmed" << std::endl;
            }
            else
            {
                currentSelection = 0;
                return true;
            }
        }
    }
    if (cs[playerNo]->bButton)
    {
        cs[playerNo]->bButton=false;
        if (pConfirm[playerNo]==true)
        {
            pConfirm[playerNo]=false;
        }
        else
        {
            currentSelection=1;
            return true;
        }
    }
    if(cs[playerNo]->leftStickVertical<0 && cs[playerNo]->leftStickHorizontal>0 && !(pConfirm[playerNo]))
    {
        pTeam[playerNo]=2;
    }
    if(cs[playerNo]->leftStickVertical>0 && cs[playerNo]->leftStickHorizontal>0 && !(pConfirm[playerNo]))
    {
        pTeam[playerNo]=4;
    }
    if(cs[playerNo]->leftStickVertical>0 && cs[playerNo]->leftStickHorizontal<0 && !(pConfirm[playerNo]))
    {
        pTeam[playerNo] = 3;
    }
    if(cs[playerNo]->leftStickVertical<0 && cs[playerNo]->leftStickHorizontal<0&& !(pConfirm[playerNo]))
    {
        pTeam[playerNo] = 1;
    }
    if(cs[playerNo]->leftStickVertical==0 && !(pConfirm[playerNo]))
    {
        pTeam[playerNo]=0;
    }
    if(cs[playerNo]->leftStickHorizontal==0 &&!(pConfirm[playerNo]))
    {
        pTeam[playerNo]=0;
    }
    return false;
}

void menu::drawPlayMenu()
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

void menu::teamSelectionMenu()
{
    std::cout<<"in team selection"<<std::endl;
    bool quit = false;
    bool confirm = false;
    currentSelection=0;
    while (ui->play() and (!quit))
    {
        for (int i=0;i<SDL_NumJoysticks();i++)
        {
            if(teamSelectionHandleInputs(ui->getCS(),i)==true)
            {
                confirm=true;
            }
        }
        if (confirm && currentSelection==0)
        {
            mapSelectionMenu();
            confirm=false;
        }
        if (confirm && currentSelection==1)
        {
            confirm=false;
            quit =true;
        }
        drawTeamSelectionMenu();
    }
}

void menu::drawTeamSelectionMenu()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,nbPlayerBackgroundTexture,NULL,NULL);
    SDL_Rect tmp;
    for (int i=0;i<SDL_NumJoysticks();i++)
    {
        std::cout<<SDL_NumJoysticks()<<std::endl;
        switch (i)
        {
            case 0:
                tmp=xboxRect[pTeam[i]];
                SDL_RenderCopy(gRenderer,xboxControllerTexture,NULL,&tmp);
                break;
            case 1:
                tmp = xboxRect[pTeam[i]];
                tmp.x += 100;
                SDL_RenderCopy(gRenderer,xboxControllerTexture,NULL,&tmp);
                break;
            case 2:
                tmp=xboxRect[pTeam[i]];
                tmp.x+=100;
                tmp.y+=50;
                SDL_RenderCopy(gRenderer,xboxControllerTexture,NULL,&tmp);
                break;
            case 3:
                tmp=xboxRect[pTeam[i]];
                tmp.y+=50;
                SDL_RenderCopy(gRenderer,xboxControllerTexture,NULL,&tmp);
                break;
        }
    }
    SDL_RenderPresent(gRenderer);
}

void menu::mapSelectionMenu()
{
    this->lc = new levelCreator(gRenderer,pTeam);
    l=lc->parse();
    l->play();
    return;
}