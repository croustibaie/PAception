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
    SDL_Texture* helloTexture; // Texture for background
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,&gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load medias for background image and red square
        const char* path = "./hello_world.bmp";
        loadMedia(&helloTexture,&gRenderer,path);
        path= "./red.bmp";

        //Create the red bloc
        //Create the level
        level l = level(helloTexture,gRenderer);
        bloc b = bloc(&gRenderer,path,&l) ;
        l.insertBlocs(&b,1);
        l.play();
    }

    //Free resources and close SDL
    SDL_DestroyTexture(helloTexture);

    close(gRenderer,gWindow,gGameController);
    return 0;
}