//
// Created by geabitbol on 09/03/16
//

#include"../headers/sound.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

void music( const char * waves) {
    Mix_Chunk*  sounds;

    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0)
    {
        std::cout <<"Couldn't open audio device: " <<Mix_GetError()
        <<std::endl;
        return;
    }

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");

    sounds = Mix_LoadWAV(waves);

        if (sounds == NULL)
        {
            std::cout << "Loading sound " << waves << " failed:"
            << Mix_GetError() << std::endl;
            return;
        }

    Mix_PlayChannel(-1, sounds, 0);
    std::cout << "Sound played" << std::endl;

}
