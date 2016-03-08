//
// Created by croustibaie on 3/7/16.
//

#include "../headers/factory.h"
#include "../headers/laserBloc.h"

factory::factory()
{

}
factory::factory(level* l) {
    this->l = l;
}

factory::~factory()
{

}


bloc* factory::createBloc(enum kind k,level* l, SDL_Renderer** gRenderer)
{
    switch (k)
    {
        case LASER:
            laserBloc* laser= createLaser(l,gRenderer);
            this->blocMap.insert(std::pair<int,bloc*>(laser->getBlocId(),laser));
            return laser;
    }

}

laserBloc* factory::createLaser(level* l, SDL_Renderer** gRenderer)
{
    laserBloc* laser= new laserBloc(gRenderer,"./black.bmp",l,200,30,1,0);
    return laser;
}

