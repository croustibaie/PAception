//
// Created by croustibaie on 1/10/16.
//

#include "../headers/sdlconfig.h"
#include <SDL_image.h>


bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_GameController** gGameController)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");//Seems to be essential if we want to capture correct inputs
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO ) < 0 )
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
            for (int i=0;i<SDL_NumJoysticks();i++)
            {
                gGameController[i] = SDL_GameControllerOpen(i);

                if (gGameController[i] == NULL) {
                    std::cout << "unable to open controller" << std::endl;
                }
                if (SDL_IsGameController(0)) {
                    std::cout << "It is a good controller" << std::endl;
                }
            }
        }
        int imgFlags=IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL image could not initialize\n");
            success=false;
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
    SDL_Surface* gSurface=NULL;
    //Load splash image
   // gSurface = SDL_LoadBMP(path);
    gSurface = IMG_Load(path);
    if( gSurface == NULL )
    {
        printf( "Unable to load image %s! ", SDL_GetError() );
        success = false;
    }
    else
    {
        *gTexture=SDL_CreateTextureFromSurface(*gRender,gSurface);
    }
    SDL_FreeSurface(gSurface);

    return success;
}

void close(SDL_Renderer* gRenderer, SDL_Window* gWindow, SDL_GameController** gGameController)
{
    //Deallocate surface
    SDL_DestroyRenderer(gRenderer);
    for (int i=0;i<SDL_NumJoysticks();i++)
    {
        SDL_GameControllerClose( gGameController[i] );
    }
    delete [](gGameController);
    //delete[] gGameController;
    //Destroy window
    SDL_DestroyWindow( gWindow );
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

