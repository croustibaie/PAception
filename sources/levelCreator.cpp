//
// Created by croustibaie on 3/12/16.
//


#include "../headers/levelCreator.h"
#include "../headers/level.h"
#include "../headers/playerBloc.h"
#include "../headers/pulseBloc.h"
#include "../headers/voidBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/bumpBloc.h"
#include "../libs/rapidxml/rapidxml.hpp"
#include "../libs/rapidxml/rapidxml_utils.hpp"
#include "../headers/mirrorBloc.h"
#include "../headers/freezeBloc.h"
#include "../headers/teleBloc.h"
#include "../headers/diamondBloc.h"
#include "../headers/lifeBloc.h"

using namespace rapidxml;

levelCreator::levelCreator()
{
    blocArray= new bloc*[NB_BLOC];
    numBloc=0;
    l= new level();
}
levelCreator::levelCreator(SDL_Renderer* gRenderer, int pTeam[4])
{
    blocArray= new bloc*[NB_BLOC];
    numBloc=0;
    if (gRenderer==NULL)
    {
        std::cout<<"renderer is null"<<std::endl;
    }
    std::cout<<"lc creating level"<<std::endl;
    this->l= new level(gRenderer,1);
    this->playerIndex=0;
    for (int i=0;i<4;i++)
    {
        this->pTeam[i]=pTeam[i];
    }
    this->textures= new textureMaster(gRenderer);
    if (textures->getTexture(3)==NULL)
    {
        std::cout<<"in lc, the texture from texture creator is null"<<std::endl;
    }
}

levelCreator::~levelCreator()
{
    for (int i=0; i<numBloc;i++)
    {
        delete blocArray[i];
    }
    delete[](this->blocArray);
    delete(this->l);
    delete (this->textures);
}

level* levelCreator::parse(std::string path)
{
    std::string type;
    int xpos;
    int ypos;
    xml_document<> doc; //create xml_document object
    file<> xmlFile(path.c_str()); //open file
    doc.parse<0>(xmlFile.data()); //parse the contents of file
    xml_node<>* root = doc.first_node("root");//find our root node
    xml_node<>* n;
    for(n=root->first_node() ; n ;n=n->next_sibling())
    {
        xml_node<>* objectNode= n->first_node();
        type= objectNode->value();

        if (type=="tele")
        {
            // creating the first telebloc
            objectNode=objectNode->next_sibling();
            int xpos1=atoi(objectNode->value());
            objectNode=objectNode->next_sibling();
            int ypos1=atoi(objectNode->value());

            // creating the second telebloc
            objectNode=objectNode->next_sibling();
            int xpos2=atoi(objectNode->value());
            objectNode=objectNode->next_sibling();
            int ypos2=atoi(objectNode->value());

            createTeleBlocs(xpos1,ypos1,xpos2,ypos2);
        }
        else
        {
            objectNode=objectNode->next_sibling();
            xpos=atoi(objectNode->value());
            objectNode=objectNode->next_sibling();
            ypos=atoi(objectNode->value());
            createObject(type,xpos,ypos);
        }

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
        blocArray[numBloc]= new pulseBloc(l->getRenderer(),textures->getTexture(11),textures->getTexture(13),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a pulse at"<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="static")
    {
        blocArray[numBloc]= new staticBloc(l->getRenderer(),textures->getTexture(12),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a static at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="void")
    {
        blocArray[numBloc]= new voidBloc(l->getRenderer(),textures->getTexture(9),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a void at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="bump")
    {
        blocArray[numBloc]= new bumpBloc(l->getRenderer(),textures->getTexture(14),l,xpos,ypos,0,0);
        numBloc++;
        std::cout<<"creating a bump at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="mirror")
    {
        blocArray[numBloc]= new mirrorBloc(l->getRenderer(),textures->getTexture(8),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a mirror at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="freeze")
    {
        blocArray[numBloc]= new freezeBloc(l->getRenderer(),textures->getTexture(10),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a freeze at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="diamond")
    {
        blocArray[numBloc]= new diamondBloc(l->getRenderer(),textures->getTexture(15),textures->getTexture(13),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a freeze at "<<xpos<< " , " <<ypos<<std::endl;
    }
    if (type=="player")
    {
        if(pTeam[this->playerIndex]!=0)
        {
            int teamColor=this->pTeam[this->playerIndex]-1;
            blocArray[numBloc] = new playerBloc(l->getRenderer(),textures->getTexture(teamColor),textures->getTexture((4+teamColor)), l, this->playerIndex,this->pTeam[this->playerIndex], xpos, ypos);
            numBloc++;
            playerIndex++;
            std::cout << "creating a player at " << xpos << " , " << ypos << std::endl;
        }
        else
        {
            playerIndex++;
        }
    }
    if (type=="life")
    {
        blocArray[numBloc]= new lifeBloc(l->getRenderer(),textures->getTexture(16),l,xpos,ypos);
        numBloc++;
        std::cout<<"creating a life at "<<xpos<< " , " <<ypos<<std::endl;
    }
}

void levelCreator::createTeleBlocs(int xpos1 , int ypos1 , int xpos2 , int ypos2)
{
    teleBloc *t1 = new teleBloc(l->getRenderer(),textures->getTexture(10),l,xpos1,ypos1);
    teleBloc *t2 = new teleBloc(l->getRenderer(),textures->getTexture(10),l,xpos2,ypos2);

    t1->setTeleBloc(t2) ;

    blocArray[numBloc] = t1;
    blocArray[numBloc+1] = t2;

    numBloc+=2;

    std::cout<<"creating a pair of teleblocs at "<<xpos1<< " , " <<ypos1<<
                                           "and" <<xpos2<< " , " <<ypos2<< std::endl;
}

