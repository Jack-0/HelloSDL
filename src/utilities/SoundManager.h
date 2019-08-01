//
// Created by jack on 31/07/19.
//

#ifndef HELLOSDL_SOUNDMANAGER_H
#define HELLOSDL_SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class SoundManager
{
public:

    static SoundManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new SoundManager();
            return s_pInstance;
        }
    }


    std::map<std::string, Mix_Chunk*> soundMap;

    bool load(std::string filepath, std::string id);
    void play(std::string id);
    void clearFromSoundMap(std::string id);

private:
    SoundManager();
    ~SoundManager();
    static SoundManager* s_pInstance;
};

typedef SoundManager TheSoundManager;


#endif //HELLOSDL_SOUNDMANAGER_H
