//
// Created by croustibaie on 3/12/16.
//


#include "../headers/levelCreator.h"
#include "../headers/level.h"
#include "../headers/playerBloc.h"
#include "../headers/pulseBloc.h"
#include "../headers/voidBloc.h"
#include "../headers/staticBloc.h"
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;


levelCreator::levelCreator()
{
    blocArray= new bloc*[30];
    numBloc=0;
    l= new level();
}
levelCreator::levelCreator(SDL_Renderer* gRenderer, int numPlayers)
{
    blocArray= new bloc*[30];
    numBloc=0;
    if (gRenderer==NULL)
    {
        std::cout<<"renderer is null"<<std::endl;
    }
    std::cout<<"lc creating level"<<std::endl;
    this->l= new level(gRenderer,1);
    this->numPlayers=numPlayers;
    this->playerIndex=0;
}

levelCreator::~levelCreator()
{
    for (int i=0; i<numBloc;i++)
    {
        delete blocArray[i];
    }
    delete[](this->blocArray);
    delete(this->l);
}

level* levelCreator::parse()
{
    std::string type;
    int xpos;
    int ypos;
    xml_document<> doc; //create xml_document object
    file<> xmlFile("./levels/showDown.xml"); //open file
    doc.parse<0>(xmlFile.data()); //parse the contents of file
    xml_node<>* root = doc.first_node("root");//find our root node
    xml_node<>* n;
    for(n=root->first_node() ; n ;n=n->next_sibling())
    {
        xml_node<>* objectNode= n->first_node();
        type= objectNode->value();
        objectNode=objectNode->next_sibling();
        xpos=atoi(objectNode->value());
        objectNode=objectNode->next_sibling();
        ypos=atoi(objectNode->value());
        createObject(type,xpos,ypos);
    }
    for (int i=0;i<numBloc;i++)
    {
        l->insertBloc(blocArray[i]);
    }
    return l;
}

void levelCreator::createObject(std::string type, int xpos, int ypos)
{
    if (type=="pulse")
    {
        blocArray[numBloc]= new pulseBloc(l->getRenderer(),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a pulse at"<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="static")
    {
        blocArray[numBloc]= new staticBloc(l->getRenderer(),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a static at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="void")
    {
        blocArray[numBloc]= new voidBloc(l->getRenderer(),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a void at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="player")
    {
        if(this->playerIndex<numPlayers)
        {
            blocArray[numBloc] = new playerBloc(l->getRenderer(), l, this->playerIndex, xpos, ypos);
            numBloc++;
            playerIndex++;
            std::cout << "creating a player at " << xpos << " , " << ypos << std::endl;
        }
    }
}