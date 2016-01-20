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

//Renderer linked to the gWindow
SDL_Renderer* gRenderer;
// 1st controller
SDL_GameController* gGameController = NULL;
// Joystick deadzone
int JOYSTICK_DEAD_ZONE = 8000;

int main( int argc, char* args[] )
{
    SDL_Texture* helloTexture;
    SDL_Texture* redTexture;
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,&gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        char* path = "/home/croustibaie/Documents/PAception/hello_world.bmp";
        loadMedia(&helloTexture,&gRenderer,path);
        path= "/home/croustibaie/Documents/PAception/red.bmp";
        loadMedia(&redTexture,&gRenderer,path);
        //Apply the image
        bloc b = bloc(&gRenderer,path) ;
        int xDir=0;
        int yDir=0;
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
           while (SDL_PollEvent(&e) != 0 && !quit)
           {
               if( e.type == SDL_QUIT )
               {
                   quit = true;
               }
               else if( e.type == SDL_JOYAXISMOTION )
               {
                   //Motion on controller 0
                   //printf("detected move\n");
                   if( e.jaxis.which == 0 )
                   {
                       //X axis motion
                       if( e.jaxis.axis == 0 )
                       {
                           //printf("x : %d\n", e.jaxis.value);
                           //Left of dead zone
                           if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                           {
                               xDir = -1;
                           }
                               //Right of dead zone
                           else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                           {
                               xDir =  1;
                           }
                           else
                           {
                               xDir = 0;
                           }
                       }
                           //Y axis motion
                       else if( e.jaxis.axis == 1 )
                       {
                     //      printf("y : %d\n", e.jaxis.value);
                           //Below of dead zone
                           if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                           {
                               yDir = -1;
                           }
                               //Above of dead zone
                           else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                           {
                               yDir =  1;
                           }
                           else
                           {
                               yDir = 0;
                           }
                       }
                   }
               }



                if (e.type==SDL_KEYDOWN)
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

            }
            b.move(xDir*4,yDir*4);
            SDL_BlitScaled(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_RenderClear(gRenderer);
            SDL_RenderCopy(gRenderer,helloTexture, NULL, NULL );
            b.draw(gRenderer);


            //Update the surface
            SDL_RenderPresent(gRenderer);
        }


    }

    //Free resources and close SDL
    close(gScreenSurface,gWindow,gGameController);

    return 0;
}