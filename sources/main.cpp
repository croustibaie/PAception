#include <SDL.h>
#include <unistd.h>
#include <SDL_mixer.h>
#include "../headers/playerBloc.h"
#include "../headers/voidBloc.h"
#include "../headers/laserBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/level.h"
#include "../headers/freezeBloc.h"
#include "../headers/sound.h"
//Screen dimension constants



int main( int argc, char* args[] )
{
//The window we'll be rendering to
    SDL_Window* gWindow = NULL;
//Renderer linked to the gWindow
    SDL_Renderer* gRenderer;
// 1st controller
    SDL_GameController** gGameController = new SDL_GameController*[4];
    SDL_Texture* helloTexture; // Texture for background
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        loadMedia(&helloTexture,&gRenderer,"./textures/loading.png");
        SDL_RenderCopy(gRenderer,helloTexture,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        //Load medias for background image and red square
        const char* path = "./textures/fond1230x960.jpg";
        loadMedia(&helloTexture,&gRenderer,path);
        path= "./textures/carre.png";
        const char* laserpath="./textures/red.png";
        const char* staticpath="./textures/black.bmp";
        const char* voidpath="./textures/black.bmp";
        const char* media="./sounds.wav";
        const char* freezepath="./textures/green.bmp";
        std::cout<<SDL_NumJoysticks()<<std::endl;
        //Create the red bloc
        //Create the level
        bool gameOn =true;
        while(gameOn)
        {
            level l = level(helloTexture,gRenderer,SDL_NumJoysticks());
            playerBloc b = playerBloc(&gRenderer,path,&l,0,0,0) ;
            staticBloc b2 = staticBloc(&gRenderer,staticpath,&l,300,149);
            freezeBloc b2bis = freezeBloc(&gRenderer,freezepath,&l,100,149);
            //laserBloc b2= laserBloc(&gRenderer,laserpath,&l,100,30,1,0);
            laserBloc b3= laserBloc(&gRenderer,laserpath,&l,200,30,1,1);
            laserBloc b4= laserBloc(&gRenderer,laserpath,&l,400,150,-1,1);
            staticBloc s1 = staticBloc(&gRenderer,staticpath,&l,300,500);
            voidBloc v= voidBloc(&gRenderer,voidpath,&l,400,400);
            l.insertBlocs(&v,1);
            l.insertBlocs(&b,1);
            l.insertBlocs(&b2,1);
            l.insertBlocs(&b2bis,1);
            //l.insertBlocs(&b3,1);
            l.insertBlocs(&s1,1);
            //l.play();
            playerBloc b1 = playerBloc(&gRenderer,path,&l,1,400,500) ;
            l.insertBlocs(&b1,1);
            //music(media);
            enum gameStatus  a = l.play();
            if(a == GAMEOVER)
            {
                char result[50];
                bool input = false;
                if(l.getNum()>=1)
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
        }
    }

    //Free resources and close SDL
    SDL_DestroyTexture(helloTexture);

    close(gRenderer,gWindow,gGameController);
    return 0;
}