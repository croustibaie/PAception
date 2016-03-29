//
// Created by croustibaie on 3/22/16.
//

#include "../headers/textureMaster.h"

textureMaster::textureMaster(SDL_Renderer *gRenderer)
{
    this->gRenderer=gRenderer;
    loadMedia(&(this->textureArray[0]),&gRenderer,"./textures/squarerouge.png");
    loadMedia(&(this->textureArray[1]),&gRenderer,"./textures/squarebleu.png");
    loadMedia(&(this->textureArray[2]),&gRenderer,"./textures/squarevert.png");
    loadMedia(&(this->textureArray[3]),&gRenderer,"./textures/squareviolet.png");
    loadMedia(&(this->textureArray[4]),&gRenderer,"./textures/laserrouge.png");
    loadMedia(&(this->textureArray[5]),&gRenderer,"./textures/laserbleu.png");
    loadMedia(&(this->textureArray[6]),&gRenderer,"./textures/laservert.png");
    loadMedia(&(this->textureArray[7]),&gRenderer,"./textures/laserviolet.png");
    loadMedia(&(this->textureArray[8]),&gRenderer,"./textures/blocdiamant3.png");
    loadMedia(&(this->textureArray[9]),&gRenderer,"./textures/void.png");
    loadMedia(&(this->textureArray[10]),&gRenderer,"./textures/freeze2.png");
    loadMedia(&(this->textureArray[11]),&gRenderer,"./textures/pulsebloc.png");
    loadMedia(&(this->textureArray[12]),&gRenderer,"./textures/blocfixe3.png");
    loadMedia(&(this->textureArray[13]),&gRenderer,"./textures/laserjaune.png");
    loadMedia(&(this->textureArray[14]),&gRenderer,"./textures/bump2.png");
    loadMedia(&(this->textureArray[15]),&gRenderer,"./textures/fleche.png");
    loadMedia(&(this->textureArray[16]),&gRenderer,"./textures/healbloc.png");
    loadMedia(&(this->textureArray[17]),&gRenderer,"./textures/teleporterbloc.png");
    loadMedia(&(this->textureArray[18]),&gRenderer,"./textures/goldensquare.png");
}

textureMaster::~textureMaster() //TODO: Investigate on how to correctly delete
{
    for (int i=0 ; i< 17;i++)
    {
        if(textureArray[i]!=NULL)
        {
            SDL_DestroyTexture(textureArray[i]);
        }
    }
}


SDL_Texture* textureMaster::getTexture(int index)
{
    if (textureArray[index]==NULL)
    {
        std::cout<<"returning a null pointer in get texture"<<  index << " "<<std::endl;
    }
    return textureArray[index];
}