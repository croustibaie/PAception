//
// Created by croustibaie on 3/7/16.
//

#ifndef PACEPTION_FACTORY_H
#define PACEPTION_FACTORY_H

class level;
class laserBloc;
class bloc;

#include <map>
#include "sdlconfig.h"

class factory {
        private :
            std::map<int, bloc*> blocMap;
           // level *l;

        public :
            factory();

          //  factory(level *l);

            ~factory();

            bloc *createBloc(enum kind k,level* l);

            laserBloc *createLaser(level* l);

         //   void setLevel(level *l);
        };


#endif //PACEPTION_FACTORY_H
