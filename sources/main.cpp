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
#include "../headers/sound.h"
#include "../headers/levelCreator.h"
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
    else
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
            playerBloc* b =new playerBloc(&gRenderer,l,0,0,0) ;
            staticBloc* b2 =new staticBloc(&gRenderer,l,300,149);
            freezeBloc* b2bis =new freezeBloc(&gRenderer,l,100,149);
            pulseBloc* b5= new pulseBloc(&gRenderer, l, 600,350);
            diamondBloc* s1 =new  diamondBloc(&gRenderer,l,300,500);
            voidBloc* v= new voidBloc(&gRenderer,l,400,400);
            l->insertBloc(v);
            l->insertBloc(b);
            l->insertBloc(b5);
            l->insertBloc(b2bis);
            l->insertBloc(b2);
            //l.insertBlocs(&b3,1);
            l->insertBloc(&*s1);
            //l.play();
            playerBloc* b1 =new playerBloc(&gRenderer,l,1,400,500) ;
          //  l.insertBlocs(&b1,1);
            //music(media);
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
            delete(b2);
            delete(b2bis);
            delete(v);
            delete(b5);
            delete(s1);
        }
    }

    //Free resources and close SDL
    close(gRenderer,gWindow,gGameController);
    return 0;
}