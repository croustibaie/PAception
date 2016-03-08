//
// Created by croustibaie on 3/7/16.
//

#ifndef PACEPTION_FACTORY_H
#define PACEPTION_FACTORY_H

class laserBloc;
class bloc;
class level;

#include <map>
#include "sdlconfig.h"

class factory {
        private :
            std::map<int, bloc*> blocMap;
            level *l;

        public :
            factory();

            factory(level *l);

            ~factory();

            bloc* createBloc(enum kind k,level* l, SDL_Renderer** gRenderer);

            laserBloc *createLaser(level* l, SDL_Renderer** gRenderer);

            void setLevel(level *l);
        };


#endif //PACEPTION_FACTORY_H
