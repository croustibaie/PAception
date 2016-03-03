//
// Created by croustibaie on 1/10/16.
//

#include "../headers/sdlconfig.h"



bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_GameController** gGameController)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");//Seems to be essential if we want to capture correct inputs
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
            /*SDL_Joystick* joystick=SDL_GameControllerGetJoystick(*gGameController);
            std::cout<< "axes :"<<SDL_JoystickNumAxes(joystick)<<std::endl;
            std::cout<<"buttons :" <<SDL_JoystickNumButtons(joystick)<<std::endl;
            std::cout<<"hats :" <<SDL_JoystickNumHats(joystick)<<std::endl;
            */ // Unquote to get joystick's specs
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
            *gRenderer = SDL_CreateRenderer( *gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( *gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia(SDL_Texture** gTexture,SDL_Renderer** gRender, char const* path)
{
    //Loading success flag
    bool success = true;
    SDL_Surface* gSurface;
    //Load splash image
    gSurface = SDL_LoadBMP(path);
    if( gSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
        success = false;
    }
    else
    {
        *gTexture=SDL_CreateTextureFromSurface(*gRender,gSurface);
    }

    return success;
}

void close(SDL_Renderer* gRenderer, SDL_Window* gWindow, SDL_GameController* gGameController)
{
    //Deallocate surface
    SDL_DestroyRenderer(gRenderer);
    SDL_GameControllerClose( gGameController );
    //Destroy window
    SDL_DestroyWindow( gWindow );
    //Quit SDL subsystems
    SDL_Quit();
}
