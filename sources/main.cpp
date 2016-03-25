#include <SDL.h>
#include <unistd.h>
#include <SDL_mixer.h>
#include "../headers/playerBloc.h"
#include "../headers/voidBloc.h"
#include "../headers/laserBloc.h"
#include "../headers/diamondBloc.h"
#include "../headers/staticBloc.h"
#include "../headers/level.h"
#include "../headers/pulseBloc.h"
#include "../headers/freezeBloc.h"
#include "../headers/mirrorBloc.h"
#include "../headers/sound.h"
#include "../headers/levelCreator.h"
#include "../headers/bumpBloc.h"
#include "../headers/menu.h"
#include "../headers/teleBloc.h"
//Screen dimension constants



int main( int argc, char* args[] )
{
//The window we'll be rendering to
    SDL_Window* gWindow = NULL;
//Renderer linked to the gWindow
    SDL_Renderer* gRenderer;
// 1st controller
    SDL_GameController** gGameController = new SDL_GameController*[4];
    //Start up SDL and create window
    if( !init(&gWindow,&gRenderer,gGameController) )
    {
        printf( "Failed to initialize!\n" );
    }
    menu m = menu(gRenderer);
    m.playMenu();
    //Free resources and close SDL
    close(gRenderer,gWindow,gGameController);
    return 0;
}