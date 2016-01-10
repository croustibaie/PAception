#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "../headers/sdlconfig.h"
//Screen dimension constants




//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Surface* gRed=NULL;



int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init(&gWindow,&gScreenSurface) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        char const* path = "/home/croustibaie/Documents/PAception/hello_world.bmp";
        loadMedia(&gHelloWorld,path);
        path= "/home/croustibaie/Documents/PAception/red.bmp";
        loadMedia(&gRed,path);
        //Apply the image
        SDL_Rect destrect;
        destrect.x=20;
        destrect.y=20;
        destrect.h=220;
        destrect.w=220;
        if (SDL_BlitScaled( gHelloWorld, NULL, gScreenSurface, NULL )!=0)
                std::cout << "blit error"<< SDL_GetError() <<std::endl;
        SDL_BlitScaled(gRed,NULL,gScreenSurface,&destrect);
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );

        //Wait two seconds
        SDL_Delay( 2000 );

    }

    //Free resources and close SDL
    close(gScreenSurface,gWindow);

    return 0;
}