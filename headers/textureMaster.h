//
// Created by croustibaie on 3/22/16.
//

#ifndef PACEPTION_TEXTUREMASTER_H
#define PACEPTION_TEXTUREMASTER_H
#include <SDL_surface.h>
#include "sdlconfig.h"

class textureMaster {
private:
    SDL_Renderer *gRenderer;
    SDL_Texture* textureArray[16];
public:
    textureMaster(SDL_Renderer *gRenderer);
    ~textureMaster();
    SDL_Texture* getTexture(int index);
};


#endif //PACEPTION_TEXTUREMASTER_H
