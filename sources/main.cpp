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
//Renderer linked to the gWindow
SDL_Renderer* gRenderer;
// 1st controller
SDL_GameController* gGameController = NULL;
// Joystick deadzone
int JOYSTICK_DEAD_ZONE = 8000;

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
        int xDir=0;
        int yDir=0;
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
           while (SDL_PollEvent(&e) != 0)
           {
               if( e.type == SDL_QUIT )
               {
                   quit = true;
               }
               else if( e.type == SDL_JOYAXISMOTION )
               {
                   //Motion on controller 0
                   printf("detected move\n");
                   if( e.jaxis.which == 0 )
                   {
                       //X axis motion
                       if( e.jaxis.axis == 0 )
                       {
                           printf("x : %d\n", e.jaxis.value);
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

            b.move(xDir,yDir);
                /*if(e.type==SDL_JOYAXISMOTION)
                {
                    if (e.jaxis.value<-DEADZONE )
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
                }*/
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