#include <SDL.h>
#include <unistd.h>
#include "../headers/playerBloc.h"
#include "../headers/laserBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/level.h"
#include "../headers/freezeBloc.h"
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
        loadMedia(&helloTexture,&gRenderer,"./loading.png");
        SDL_RenderCopy(gRenderer,helloTexture,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        //Load medias for background image and red square
        const char* path = "./leather.bmp";
        loadMedia(&helloTexture,&gRenderer,path);
        path= "./carre.png";
        const char* laserpath="./red.png";
        const char* staticpath="./black.bmp";
        const char* freezepath="./green.bmp";
        std::cout<<SDL_NumJoysticks()<<std::endl;
        //Create the red bloc
        //Create the level
        level l = level(helloTexture,gRenderer);
        playerBloc b = playerBloc(&gRenderer,path,&l,0,0,0) ;
        staticBloc b2 = staticBloc(&gRenderer,staticpath,&l,300,149);
        freezeBloc b2bis = freezeBloc(&gRenderer,freezepath,&l,100,149);
        //laserBloc b2= laserBloc(&gRenderer,laserpath,&l,100,30,1,0);
        laserBloc b3= laserBloc(&gRenderer,laserpath,&l,200,30,1,1);
        laserBloc b4= laserBloc(&gRenderer,laserpath,&l,400,150,-1,1);
        staticBloc s1 = staticBloc(&gRenderer,staticpath,&l,300,500);
        l.insertBlocs(&b,1);
        l.insertBlocs(&b2,1);
        l.insertBlocs(&b2bis,1);
        //l.insertBlocs(&b3,1);
        l.insertBlocs(&s1,1);
        //l.play();
        playerBloc b1 = playerBloc(&gRenderer,path,&l,1,400,400) ;
        //l.insertBlocs(&b1,1);
        l.play();
    }

    //Free resources and close SDL
    SDL_DestroyTexture(helloTexture);

    close(gRenderer,gWindow,gGameController);
    return 0;
}