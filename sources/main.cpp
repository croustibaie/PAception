#include <SDL.h>
#include <unistd.h>
#include <SDL_mixer.h>
#include "../headers/playerBloc.h"
#include "../headers/voidBloc.h"
#include "../headers/laserBloc.h"
#include "../headers/diamondBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/level.h"
#include "../headers/pulseBloc.h"
#include "../headers/freezeBloc.h"
#include "../headers/mirrorBloc.h"
#include "../headers/sound.h"
#include "../headers/levelCreator.h"
#include "../headers/bumpBloc.h"
#include "../headers/menu.h"
#include "../headers/teleBloc.h"
//Screen dimension constants



int main( int argc, char* args[] )
{
//The window we'll be rendering to
    SDL_Window* gWindow = NULL;
//Renderer linked to the gWindow
    SDL_Renderer* gRenderer;
// 1st controller
    SDL_GameController** gGameController = new SDL_GameController*[4];
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    menu m = menu(gRenderer);
    m.playMenu();
   /* else
    {
        //Load medias for background image and red square
        const char* media="./sounds.wav";
        std::cout<<SDL_NumJoysticks()<<std::endl;
        //Create the red bloc
        //Create the level
        bool gameOn =true;
        while(gameOn)
        {
            //level l = level(gRenderer,SDL_NumJoysticks());
            levelCreator* lc= new levelCreator(gRenderer);
            level* l= lc->parse();
            //level* l = new level(gRenderer,1);
            playerBloc* b =new playerBloc(&gRenderer,l,0,400,0) ;
            //mirrorBloc* b2 =new mirrorBloc(&gRenderer,l,300,149);
            //freezeBloc* b2bis =new freezeBloc(&gRenderer,l,100,149);
            //pulseBloc* b5= new pulseBloc(&gRenderer, l, 600,350);
            //diamondBloc* s1 =new  diamondBloc(&gRenderer,l,300,500);
            //voidBloc* v= new voidBloc(&gRenderer,l,400,400);
            bumpBloc* bp1= new bumpBloc(&gRenderer,l,600,200,(float) 0,(float) 0);
            bumpBloc* bp2= new bumpBloc(&gRenderer,l,400,200,(float) 0,(float) 0);
            //l->insertBloc(v);

            //teleBloc* t1 = new teleBloc(&gRenderer,l,400,400);
            //teleBloc* t2 = new teleBloc(&gRenderer,l,100,300);

            //t2->setteleBloc(t1);
             l->insertBloc(b);
             l->insertBloc(bp1);
             l->insertBloc(bp2);
            //l->insertBloc(t1);
            //l->insertBloc(t2);



            //l.insertBlocs(&b3,1);

            //l.play();
            //playerBloc* b1 =new playerBloc(&gRenderer,l,1,400,500) ;
          //  l.insertBlocs(&b1,1);
           // music(media);
            enum gameStatus  a = l->play();
            if(a == GAMEOVER)
            {
                char result[50];
                bool input = false;
                if(l->getNum()>=1)
                {
                    std::cout<<"Do you wanna play another game ? "<<std::endl;
                    std::cout<<"y or n"<<std::endl;
                    std::cin>>result;
                    while(!(input))
                    {
                        if (strcmp(result, "y") == 0)
                        {
                            input = true;
                            std::cout << "let's play another game !" << std::endl;
                        }
                        else if (strcmp(result, "n") == 0)
                        {
                            input = true;
                            gameOn = false;
                            std::cout << "End of the game" << std::endl;
                        }
                        else
                        {
                            std::cout << "please type y or n" << std::endl;
                            std::cin >> result;
                        }
                    }
                }
                else
                {
                    std::cout<<"Please play with at least one joystick"<<std::endl;
                    gameOn=false;
                }
            }
            delete(lc);
            delete(b);

        }
    }

    //Free resources and close SDL
    close(gRenderer,gWindow,gGameController);
    return 0;
}