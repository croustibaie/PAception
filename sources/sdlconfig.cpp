//
// Created by croustibaie on 1/10/16.
//

#include "../headers/sdlconfig.h"
const int SCREEN_WIDTH = 820;
const int SCREEN_HEIGHT = 640;

bool init(SDL_Window** gWindow, SDL_Surface** gScreenSurface, SDL_GameController** gGameController)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( SDL_NumJoysticks() < 1 )
        {
            std::cout << "no joystick"<< std::endl;
        }
        else
        {
            *gGameController = SDL_GameControllerOpen( 0 );
            SDL_Joystick* joystick=SDL_GameControllerGetJoystick(*gGameController);
            std::cout<< "axes :"<<SDL_JoystickNumAxes(joystick)<<std::endl;
            std::cout<<"buttons :" <<SDL_JoystickNumButtons(joystick)<<std::endl;
            std::cout<<"hats :" <<SDL_JoystickNumHats(joystick)<<std::endl;

            if( *gGameController == NULL )
            {
                std::cout << "unable to open controller"<<std::endl;
            }
            if (SDL_IsGameController(0))
            {
                std::cout<< "It is a good controller" << std::endl;
            }
        }
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

void close(SDL_Surface* gSurface, SDL_Window* gWindow, SDL_GameController* gGameController)
{
    //Deallocate surface
    SDL_FreeSurface( gSurface );
    SDL_GameControllerClose( gGameController );
    gGameController=NULL;
    //Destroy window
    SDL_DestroyWindow( gWindow );


    //Quit SDL subsystems
    SDL_Quit();
}
