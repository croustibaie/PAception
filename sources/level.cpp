//
// Created by croustibaie on 1/23/16.
//

#include "../headers/bloc.h"
#include"./../headers/level.h"

level::level()
{
    backGroundTexture=NULL;
    lastTime=SDL_GetTicks();
    elapsedTime=0;
}

level::level (SDL_Texture* Texture,SDL_Renderer* gRenderer)
{

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
        it->second->react(ui->getCS()[0],elapsedTime); // MODIFY FOR MULTIPLAYER
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

    while(ui->play())
    {
        this->blocReactions();
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
bloc* level::collide(int blocID, SDL_Rect potentialPos)
{
    std::map<int,bloc*>::iterator it;
    for (it=blocMap.begin(); it!=blocMap.end();it++)
    {
        if (it->first!=blocID)
        {
            if (testCollision(it->second->getRect(), potentialPos))
            {
                //std::cout<<"colliding with bloc" + it->second->getBlocId()<<std::endl;
                return it->second;
            }
        }
    }
    return nullptr;
}

bool level::testCollision(SDL_Rect a, SDL_Rect b)
{
    if ((a.x + a.w < b.x) || (b.x + b.w < a.x))
    {
        return false;
    }
    if ((a.y + a.h < b.y) || (b.y + b.h < a.y))
    {
        return false;
    }
    else
    {
        return true;
    }
}


