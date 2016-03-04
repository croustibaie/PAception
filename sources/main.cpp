#include <SDL.h>
#include "../headers/playerBloc.h"
#include "../headers/laserBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/level.h"
#include "../headers/laserBloc.h"
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
        //Load medias for background image and red square
        const char* path = "./hello_world.bmp";
        loadMedia(&helloTexture,&gRenderer,path);
        path= "./red.bmp";
        std::cout<<SDL_NumJoysticks()<<std::endl;
        //Create the red bloc
        //Create the level
        level l = level(helloTexture,gRenderer);
        playerBloc b = playerBloc(&gRenderer,path,&l,0,0,0) ;
        laserBloc b2= laserBloc(&gRenderer,path,&l,150,100);
        staticBloc s1 = staticBloc(&gRenderer,path,&l,300,500);
        l.insertBlocs(&b,1);
        l.insertBlocs(&b2,1);
        l.insertBlocs(&s1,1);
        //l.play();
        playerBloc b1 = playerBloc(&gRenderer,path,&l,1,0,SCREEN_WIDTH-50) ;
        l.insertBlocs(&b1,1);
        l.play();
    }

    //Free resources and close SDL
    SDL_DestroyTexture(helloTexture);

    close(gRenderer,gWindow,gGameController);
    return 0;
}