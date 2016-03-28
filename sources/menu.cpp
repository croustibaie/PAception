//
// Created by croustibaie on 3/12/16.
//

#include "../headers/menu.h"
#include "../headers/level.h"
#include "../headers/levelCreator.h"
#include "../headers/userInterface.h"

menu::menu(SDL_Renderer *gRenderer,SDL_GameController** igGameController)
{
    this->gGameController=igGameController;
    this->gRenderer=gRenderer;
    loadMedia(&this->backGroundTexture,&gRenderer,"./textures/menuBG.png");
    loadMedia(&this->playButtonTexture,&gRenderer,"./textures/playbutton.png");
    loadMedia(&this->playButtonTextureSelected,&gRenderer,"./textures/playButtonSelected.png");
    loadMedia(&this->quitButtonTexture,&gRenderer,"./textures/quitButton.png");
    loadMedia(&this->quitButtonTextureSelected,&gRenderer,"./textures/quitButtonSelected.png");
    loadMedia(&this->nbPlayerBackgroundTexture,&gRenderer,"./textures/teamchoose.png");
    loadMedia(&this->xboxControllerTexture,&gRenderer,"./textures/xbox.png");
    loadMedia(&this->mapTextures[0],&gRenderer,"./textures/frenzyarena.png");
    loadMedia(&this->mapTextures[1],&gRenderer,"./textures/reactor.png");
    loadMedia(&this->mapTextures[2],&gRenderer,"./textures/voidlabyrinth.png");
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
    this->pPos[0]=0;
    this->pPos[1]=0;
    this->pPos[2]=0;
    this->pPos[3]=0;
    this->pConfirm[0]=false;
    this->pConfirm[1]=false;
    this->pConfirm[2]=false;
    this->pConfirm[3]=false;
    this->xboxRect[0].x=820;
    this->xboxRect[0].w=50;
    this->xboxRect[0].y=480;
    this->xboxRect[0].h=40;
    this->xboxRect[1].x=400;
    this->xboxRect[1].w=50;
    this->xboxRect[1].y=200;
    this->xboxRect[1].h=40;
    this->xboxRect[2].x=1400;
    this->xboxRect[2].w=50;
    this->xboxRect[2].y=200;
    this->xboxRect[2].h=40;
    this->xboxRect[3].x=1400;
    this->xboxRect[3].w=50;
    this->xboxRect[3].y=800;
    this->xboxRect[3].h=40;
    this->xboxRect[4].x=400;
    this->xboxRect[4].w=50;
    this->xboxRect[4].y=800;
    this->xboxRect[4].h=40;
    this->inputTimer=0;
    maps[0]="./levels/FrenzyArena.xml";
    maps[1]="./levels/reactor.xml";
    maps[2]="./levels/voidLabyrinth.xml";
}

menu::~menu()
{
    delete(this->ui);
    delete(this->lc);
    SDL_DestroyTexture(backGroundTexture);
}




void menu::playMenu()
{
    bool quit=false;
    bool confirm=false;
    while(ui->play() and (!quit))
    {
        for (int i=0;i<SDL_NumJoysticks();i++)
        {
            confirm=confirm||playMenuHandleInputs(ui->getCS(),i);
        }
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
        pTeam[playerNo]=3;
    }
    if(cs[playerNo]->leftStickVertical>0 && cs[playerNo]->leftStickHorizontal<0 && !(pConfirm[playerNo]))
    {
        pTeam[playerNo] = 4;
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
    if (cs[playerNo]->RT && SDL_GetTicks()-this->inputTimer>500)
    {
        this->pPos[playerNo]=(this->pPos[playerNo]+1)%4;
        this->inputTimer=SDL_GetTicks();
    }
    if (cs[playerNo]->LT && SDL_GetTicks()-this->inputTimer>500)
    {
        if (this->pPos[playerNo]==0)
        {
            this->pPos[playerNo]=3;
        }
        else
        {
            this->pPos[playerNo]=this->pPos[playerNo]-1;
        }
        this->inputTimer=SDL_GetTicks();
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
        if (ui->newPlayer())
        {
            gGameController[SDL_NumJoysticks()-1]=SDL_GameControllerOpen(SDL_NumJoysticks()-1);
        }
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
        switch (i)
        {
            case 0:
                tmp=xboxRect[pTeam[i]];
                SDL_RenderCopyEx(gRenderer,xboxControllerTexture,NULL,&tmp,this->pPos[i]*90,NULL,SDL_FLIP_NONE);
                break;
            case 1:
                tmp = xboxRect[pTeam[i]];
                tmp.x += 200;
                SDL_RenderCopyEx(gRenderer,xboxControllerTexture,NULL,&tmp,this->pPos[i]*90,NULL,SDL_FLIP_NONE);
                break;
            case 2:
                tmp=xboxRect[pTeam[i]];
                tmp.x+=200;
                tmp.y+=100;
                SDL_RenderCopyEx(gRenderer,xboxControllerTexture,NULL,&tmp,this->pPos[i]*90,NULL,SDL_FLIP_NONE);
                break;
            case 3:
                tmp=xboxRect[pTeam[i]];
                tmp.y+=100;
                SDL_RenderCopyEx(gRenderer,xboxControllerTexture,NULL,&tmp,this->pPos[i]*90,NULL,SDL_FLIP_NONE);
                break;
        }
    }
    SDL_RenderPresent(gRenderer);
}

void menu::mapSelectionMenu()
{
    bool back=false;
    while (!back)
    {
        this->currentSelection = 0;
        bool quit = false;
        while (ui->play() && (!quit))
        {
            for (int i = 0; i < SDL_NumJoysticks(); i++)
            {
                if (mapSelectionHandleInputs(ui->getCS(), i))
                {
                    quit = true;
                }
            }
            drawMapSelectionMenu();
        }
        if (this->currentSelection == -1)
        {
            back=true;
            return;
        }
        else
        {
            this->lc = new levelCreator(gRenderer, pTeam,pPos);
            l = lc->parse(maps[this->currentSelection]);
            while (l->play())
            {
                delete (lc);
                lc = new levelCreator(gRenderer, pTeam,pPos);
                l = lc->parse(maps[this->currentSelection]);
            }
        }
    }
    return;
}

bool menu::mapSelectionHandleInputs(controllerState **cs, int playerNo)
{
    if (cs[playerNo]->aButton)
    {
        std::cout<<"pressed a"<<std::endl;
        cs[playerNo]->aButton=false;
        return true;
    }
    if (cs[playerNo]->bButton)
    {
        cs[playerNo]->bButton=false;
        this->currentSelection=-1;
        return true;
    }
    if (cs[playerNo]->leftStickVertical>0 && SDL_GetTicks()-this->inputTimer>300)
        {
            this->currentSelection=(this->currentSelection+1)%NB_MAP;
            this->inputTimer=SDL_GetTicks();
            return false;
        }
    if (cs[playerNo]->leftStickVertical<0 && SDL_GetTicks()-this->inputTimer>300 )
    {
        if (this->currentSelection==0)
        {
            this->currentSelection=NB_MAP-1;
        }
        else
        {
            this->currentSelection--;
        }
        this->inputTimer=SDL_GetTicks();
        return false;
    }
    return false;
}

void menu::drawMapSelectionMenu()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    SDL_Rect r;
    r.x=700;
    r.w=400;
    r.y=400;
    r.h=300;
    SDL_RenderCopy(gRenderer,mapTextures[this->currentSelection],NULL,&r);
    SDL_RenderPresent(gRenderer);
}