//
// Created by jack on 31/07/19.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "SoundManager.h"


SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cout << "SDL AUDIO init failed!\n";

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        std::cout << "SDL Mixer init failed!\n";

}

bool SoundManager::load(std::string filepath, std::string id)
{
    soundMap[id] = Mix_LoadWAV(filepath.c_str());

    if(soundMap[id] == NULL)
        std::cout << "Audio file at (" << filepath << ") not found!\n";
}

void SoundManager::play(std::string id)
{
    if ( Mix_PlayChannel(-1, soundMap[id], 0) == -1 )
        std::cout << "Failed to play sound\n";
}

void SoundManager::clearFromSoundMap(std::string id)
{
    Mix_FreeChunk(soundMap[id]);
    soundMap.erase(id);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

