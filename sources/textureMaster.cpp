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
    loadMedia(&(this->textureArray[9]),&gRenderer,"./textures/bump1.png");
    loadMedia(&(this->textureArray[10]),&gRenderer,"./textures/freeze.png");
    loadMedia(&(this->textureArray[11]),&gRenderer,"./textures/pulsebloc.png");
    loadMedia(&(this->textureArray[12]),&gRenderer,"./textures/blocfixe3.png");
    loadMedia(&(this->textureArray[13]),&gRenderer,"./textures/laserjaune.png");
    loadMedia(&(this->textureArray[14]),&gRenderer,"./textures/bump2.png");
}

textureMaster::~textureMaster() //TODO: Investigate on how to correctly delete
{
    SDL_DestroyTexture(textureArray[0]);
    SDL_DestroyTexture(textureArray[1]);
    SDL_DestroyTexture(textureArray[2]);
    SDL_DestroyTexture(textureArray[3]);
    SDL_DestroyTexture(textureArray[4]);
    SDL_DestroyTexture(textureArray[5]);
    SDL_DestroyTexture(textureArray[6]);
    SDL_DestroyTexture(textureArray[7]);
    SDL_DestroyTexture(textureArray[8]);
    SDL_DestroyTexture(textureArray[9]);
    SDL_DestroyTexture(textureArray[10]);
    SDL_DestroyTexture(textureArray[11]);
    SDL_DestroyTexture(textureArray[12]);
    SDL_DestroyTexture(textureArray[13]);
    SDL_DestroyTexture(textureArray[14]);
}


SDL_Texture* textureMaster::getTexture(int index)
{
    if (textureArray[index]==NULL)
    {
        std::cout<<"returning a null pointer in get texture"<<  index << " "<<std::endl;
    }
    return textureArray[index];
}