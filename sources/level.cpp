//
// Created by croustibaie on 1/23/16.
//

#include "../headers/bloc.h"
#include "../headers/sdlconfig.h"
#include"./../headers/level.h"
#include"./../headers/userInterface.h"

level::level()
{
    backGroundTexture=NULL;
    lastTime=SDL_GetTicks();
    elapsedTime=0;
}

level::level (bloc* array,int numBlocs,SDL_Texture* Texture,SDL_Renderer* gRenderer)
{
    blocArray.reserve(numBlocs);

    for (int i=0 ; i<numBlocs;i++)
    {
        blocArray.push_back(&array[i]);
        blocMap.insert(std::pair<int,bloc*>(array[i].getBlocId(),&array[i]));
    }
    this->numBlocs=numBlocs;
    this->backGroundTexture= Texture;
    this->gRenderer=gRenderer;
}

level::~level()
{
    delete ui;
}

/* returns false with a quit command was sent and true if the event queue is null*/


void level::blocReactions()
{
    std::map<int,bloc*>::iterator it;
    for (it= blocMap.begin();it!=blocMap.end();it++)//Make sure blocMap.end is recomputed on every loop
    {
        it->second->react(ui->getCS()[0],elapsedTime); // MODIFY FOR MULTIPLAYER
    }
}

void level::blocDraw()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    std::map<int,bloc*>::iterator it;
    for (it= blocMap.begin();it!=blocMap.end();it++)//Make sure blocMap.end is recomputed on every loop
    {
        it->second->draw();
    }
    SDL_RenderPresent(gRenderer);
}
enum gameStatus level::play ()
{
    lastTime=SDL_GetTicks();
    elapsedTime=20; // We have to initialize the elapsed time for the very first frame, chose 20ms by default

    while(ui->play()==true)
    {
        blocReactions();
        unsigned tmptime= SDL_GetTicks(); //Get the number of milliseconds since the game started
        blocDraw();
        elapsedTime= tmptime-lastTime;
        lastTime=tmptime;
        //printf("elapsed time:%u \n", elapsedTime);
    }

    return PLAY;
}




