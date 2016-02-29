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

    for (int i=0 ; i<numBlocs;i++)
    {
        blocMap.insert(std::pair<int,bloc*>(array[i].getBlocId(),&array[i])); // When inserting in a map, we need to insert a pair
    }
    this->backGroundTexture= Texture;
    this->gRenderer=gRenderer;
}

level::~level()
{
    delete ui;
}

void level::blocReactions()
{
    std::map<int,bloc*>::iterator it;
    for (it= blocMap.begin();it!=blocMap.end();it++)//Make sure blocMap.end is recomputed on every loop
    {
        it->second->react(ui->getCS(),elapsedTime);
    }
}
void level::blocDraw()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    std::map<int,bloc*>::iterator it;
    for (it= blocMap.begin();it!=blocMap.end();it++)//Make sure blocMap.end is recomputed on every loop, could be the cause of seg faults
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
void level::deleteBloc(int blocID)
{
    blocMap.erase(blocID);
}
void level::insertBlocs(bloc *blocArray, int nbBlocs)
{
    for (int i=0;i<nbBlocs;i++)
    {
        blocMap.insert(std::pair<int, bloc *>(blocArray[i].getBlocId(),&blocArray[i]));
    }
}


