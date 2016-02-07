#include <SDL.h>
#include <iostream>
#include "../headers/sdlconfig.h"
#include "../headers/bloc.h"
#include "../headers/level.h"
//Screen dimension constants



int main( int argc, char* args[] )
{
//The window we'll be rendering to
    SDL_Window* gWindow = NULL;
//Renderer linked to the gWindow
    SDL_Renderer* gRenderer;
// 1st controller
    SDL_GameController* gGameController = NULL;
    SDL_Texture* helloTexture;
    SDL_Texture* redTexture;
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,&gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load medias for background image and red square
        const char* path = "/home/croustibaie/Documents/PAception/hello_world.bmp";
        loadMedia(&helloTexture,&gRenderer,path);
        std::cout<<"Media loaded"<<std::endl;
        path= "/home/croustibaie/Documents/PAception/red.bmp";
        loadMedia(&redTexture,&gRenderer,path);
        std::cout<<"Media loaded"<<std::endl;

        //Create the red bloc
        bloc b = bloc(&gRenderer,path) ;
        std::cout<<"Bloc loaded"<<std::endl;

        //Create the level
        level l = level(&b,1,helloTexture,gRenderer);
        std::cout<<"level created"<<std::endl;
        l.play();
    }

    //Free resources and close SDL
    SDL_DestroyTexture(redTexture);
    SDL_DestroyTexture(helloTexture);

    close(gRenderer,gWindow,gGameController);

    return 0;
}