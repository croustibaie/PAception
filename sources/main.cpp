#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "../headers/sdlconfig.h"
#include "../headers/bloc.h"
//Screen dimension constants




//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
// Image for the red square
SDL_Surface* gRed=NULL;
// 1st controller
SDL_GameController* gGameController = NULL;
// Joystick deadzone
int DEADZONE = 8000;

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init(&gWindow,&gScreenSurface,&gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {

        //Load media
        char* path = "/home/croustibaie/Documents/PAception/hello_world.bmp";
        loadMedia(&gHelloWorld,path);
        path= "/home/croustibaie/Documents/PAception/red.bmp";
        loadMedia(&gRed,path);
        //Apply the image
        bloc b = bloc(path) ;
        int f=0;
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0) {
                if(e.type==SDL_JOYAXISMOTION) {
                    if (e.jaxis.value<-1000 )
                    {
                        if (e.jaxis.axis==0)
                        {
                            std::cout<<"x :"<< e.jaxis.value<<std::endl;
                            if (e.jaxis.value < - DEADZONE)
                            {
                                b.move(-4,0);
                            }
                            else if(e.jaxis.value > DEADZONE)
                            {
                                std::cout<<"right"<<std::endl;
                                b.move(4,0);
                            }
                        }
                        else if (e.jaxis.axis==1)
                        {
                            std::cout<<"y :"<< e.jaxis.value<<std::endl;
                            if (e.jaxis.value< -DEADZONE)
                            {
                                b.move(0,4);
                            }
                            else if (e.jaxis.value>DEADZONE)
                            {
                                b.move(0,-4);
                            }
                        }
                    }
                }
                if (e.type == SDL_QUIT)
                {
                    std::cout<<"quit request"<<std::endl;
                    quit=true;
                }

                else if (e.type==SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            std::cout<<"up"<<std::endl;
                            b.move(0,-4);
                            break;
                        case SDLK_DOWN:
                            std::cout<<"down"<<std::endl;
                            b.move(0,4);
                            break;
                        case SDLK_LEFT:
                            std::cout<<"left"<<std::endl;
                            b.move(-4,0);
                            break;
                        case SDLK_RIGHT:
                            std::cout<<"right"<<std::endl;
                            b.move(4,0);
                            break;
                    }
                }
                SDL_BlitScaled(gHelloWorld, NULL, gScreenSurface, NULL);
                b.draw(gScreenSurface);

                f++;
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }


    }

    //Free resources and close SDL
    close(gScreenSurface,gWindow,gGameController);

    return 0;
}