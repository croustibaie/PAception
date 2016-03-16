//
// Created by croustibaie on 1/23/16.
//

#include"./../headers/level.h"
#include "../headers/laserBloc.h"

level::level()
{
    backGroundTexture=NULL;
    lastTime=SDL_GetTicks();
    elapsedTime=0;
}

level::level (SDL_Renderer* gRenderer,int numPlayer)
{
    if (gRenderer==NULL)
    {
        std::cout<<"In level constructor, no valid renderer"<<std::endl;
    }
    loadMedia(&pauseTexture,&gRenderer,"./textures/pausescreen.png");
    loadMedia(&backGroundTexture,&gRenderer,"./textures/fond1230x960.jpg");
    if (backGroundTexture==NULL)
    {
        std::cout<<"level has no background texture"<<std::endl;
    }
    this->gRenderer=gRenderer;
    if (this->gRenderer==NULL)
    {
        std::cout<<"In level constructor, no valid renderer"<<std::endl;
    }
    else
    {
        std::cout<<"valid renderer"<<std::endl;
    }
    this->numPlayer=numPlayer;
    this->gamePaused=false;
    this->pauseRect.x=SCREEN_WIDTH/8*3;
    this->pauseRect.w=SCREEN_WIDTH/4;
    this->pauseRect.y=SCREEN_HEIGHT/8*3;
    this->pauseRect.h=SCREEN_HEIGHT/6;

}

level::~level()
{
    delete ui;
}

SDL_Renderer** level::getRenderer()
{
    if (this->gRenderer==NULL)
    {
        std::cout<<"transmitting null renderer";
    }
    return &(this->gRenderer);
}

void level::blocReactions()
{
    mapReactions(&(this->SolidblocMap));
    mapReactions(&(this->NonSolidblocMap));
    mapReactions(&(this->PlayerblocMap));

}
void level::blocDraw()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer,backGroundTexture,NULL,NULL);
    std::map<int,bloc*>::iterator it;

    for (it= SolidblocMap.begin();it!=SolidblocMap.end();it++)//Make sure blocMap.end is recomputed on every loop, could be the cause of seg faults
    {
        it->second->draw();
    }

    for (it= NonSolidblocMap.begin();it!=NonSolidblocMap.end();it++)//Make sure blocMap.end is recomputed on every loop, could be the cause of seg faults
    {
        it->second->draw();
    }

    for (it= PlayerblocMap.begin();it!=PlayerblocMap.end();it++)//Make sure blocMap.end is recomputed on every loop, could be the cause of seg faults
    {
        it->second->draw();
    }
    if (gamePaused)
    {
        SDL_RenderCopy(gRenderer,pauseTexture,NULL,&(this->pauseRect));
    }

    SDL_RenderPresent(gRenderer);
}
enum gameStatus level::play ()
{
    lastTime=SDL_GetTicks();
    elapsedTime=20; // We have to initialize the elapsed time for the very first frame, chose 20ms by default

    while((ui->play())&&((this->numPlayer>1)||TEST))
    {
        while(ui->isPaused())
        {
            gamePaused=true;
            blocDraw();
            ui->play();
            lastTime=SDL_GetTicks();
        }
        gamePaused=false;
        this->blocReactions();
        unsigned tmptime= SDL_GetTicks(); //Get the number of milliseconds since the game started
        blocDraw();
        elapsedTime= tmptime-lastTime;
        lastTime=tmptime;
    }

    if((this->numPlayer)<=1)
    {
        return GAMEOVER;
    }
    else
    {
        return PLAY;
    }
}
void level::deleteBloc(int blocID , enum kind blocKind)
{

    switch (blocKind)
    {
        case SOLID :
            SolidblocMap.erase(blocID);
            break;
        case NONSOLID :
            NonSolidblocMap.erase(blocID);
            break;
        case PLAYER :
            PlayerblocMap.erase(blocID);
            this->numPlayer--;
            break;
    }
}
void level::insertBloc(bloc *b)
{
    switch (b->getKind())
    {
        case SOLID :
            SolidblocMap.insert(std::pair<int, bloc *>(b->getBlocId(), b));
            break;
        case NONSOLID :
            NonSolidblocMap.insert(std::pair<int, bloc *>(b->getBlocId(), b));
            break;
        case PLAYER :
            PlayerblocMap.insert(std::pair<int, bloc *>(b->getBlocId(), b));
            break;
    }
   /* for (int i=0;i<nbBlocs;i++)
    {

        switch (blocArray[i]->getKind())
        {
            case SOLID :
                SolidblocMap.insert(std::pair<int, bloc *>(blocArray[i]->getBlocId(), blocArray[i]));
                break;
            case NONSOLID :
                NonSolidblocMap.insert(std::pair<int, bloc *>(blocArray[i]->getBlocId(), blocArray[i]));
                break;
            case PLAYER :
                PlayerblocMap.insert(std::pair<int, bloc *>(blocArray[i]->getBlocId(), blocArray[i]));
                break;
        }
    }
    */
}


bloc* level::collide(int blocID, SDL_Rect potentialPos, std::vector<bloc*> ignoredBlocs)
{
    bloc *collidedBloc=mapCollide(blocID,potentialPos,ignoredBlocs,SolidblocMap);
    if (collidedBloc!= nullptr)
    {
        return collidedBloc;
    }
    collidedBloc=mapCollide(blocID,potentialPos,ignoredBlocs,NonSolidblocMap);
    if (collidedBloc!= nullptr)
    {
        return collidedBloc;
    }
    collidedBloc=mapCollide(blocID,potentialPos,ignoredBlocs,PlayerblocMap);
    return collidedBloc;
}

bloc* level::mapCollide(int blocID, SDL_Rect potentialPos, std::vector<bloc *> ignoredBlocs,
                        std::map<int, bloc *> map)
{
    std::map<int,bloc*>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
        if (it->first != blocID)
        {
            if (testCollision(it->second->getRect(), potentialPos))
            {
                //std::cout<<"colliding with bloc" + it->second->getBlocId()<<std::endl;
                bool notYetCollided = true;
                for (int i = 0; i < ignoredBlocs.size(); i++)
                {
                    if (ignoredBlocs.at(i)->getBlocId() == it->first)
                    {
                        notYetCollided = false;
                    }
                }
                if (notYetCollided)
                {
                    return it->second;
                }
            }
        }
    }

    return nullptr;
}


void level::mapReactions(std::map<int, bloc *> *map)
{
    std::map<int,bloc*>::iterator it;
    it= (*map).begin();
    int i=0;
    while (it!=(*map).end())//Make sure blocMap.end is recomputed on every loop
    {
        if(!(it->second->react(ui->getCS(),elapsedTime)))
        {
            it=(*map).begin();
            for (int j=0;j<i;j++)
            {
                it++;
            }
        }
        else
        {
            i++;
            it++;
        }
    }
}



bool level::testCollision(SDL_Rect a, SDL_Rect b)
{
    if ((a.x + a.w < b.x) || (b.x + b.w < a.x))
    {
        return false;
    }
    if (a.y + a.h < b.y)
    {
        return false;
    }
    if (b.y + b.h < a.y)
    {
        return false;
    }
    return true;
}

int level::getNum()
{
    return(this->numPlayer);
}

bool level::win()
{
    if(getNum() >= 2)
    {
        return(0);
    }
    else
    {
        return(1);
    }
}

int level::winnerBloc(std::map<int,bloc*> PlayerblocMap)
{
    std::map<int,bloc*>::iterator it;
    it = PlayerblocMap.begin();

    return(it->first+1);
}





