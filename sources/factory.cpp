//
// Created by croustibaie on 3/7/16.
//

#include "../headers/factory.h"

factory::factory()
{

}
/*factory::factory(level* l)
{
    this->l =l ;
}*/

factory::~factory()
{

}

bloc* factory::createBloc(enum kind k, level* l)
{
    switch (k)
    {
        case LASER:
            laserBloc* laser= createLaser(l);
            //blocMap.insert(std::pair<int,bloc*>(laser->getBlocId(),laser));
            return laser;
    }

}

laserBloc* factory::createLaser(level* l)
{
    laserBloc* laser= new laserBloc(l->getRenderer(),"./black.bmp",l,200,30,1,0);
    return laser;
}

