//
// Created by croustibaie on 1/10/16.
//

#include "../headers/sdlconfig.h"

const int SCREEN_WIDTH = 820;
const int SCREEN_HEIGHT = 640;

bool init(SDL_Window** gWindow, SDL_Surface** gScreenSurface)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        *gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( *gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            *gScreenSurface = SDL_GetWindowSurface( *gWindow );
        }
    }

    return success;
}

bool loadMedia(SDL_Surface** gSurface, char const* path)
{
    //Loading success flag
    bool success = true;

    //Load splash image
    *gSurface = SDL_LoadBMP(path);
    if( *gSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close(SDL_Surface* gSurface, SDL_Window* gWindow)
{
    //Deallocate surface
    SDL_FreeSurface( gSurface );

    //Destroy window
    SDL_DestroyWindow( gWindow );


    //Quit SDL subsystems
    SDL_Quit();
}
