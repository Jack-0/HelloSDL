//
// Created by jack on 16/03/19.
//

#ifndef HELLOSDL_TEXTUREMANAGER_H
#define HELLOSDL_TEXTUREMANAGER_H

#include <iostream>
#include <map>
#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/// A singleton that manages all game textures.

class TextureManager
{
public:
    std::map<std::string, SDL_Texture*> textureMap;

    bool load(std::string filename, std::string id, SDL_Renderer* renderer);
    bool loadWithNewColour(std::string filename, std::string id, SDL_Renderer* pRenderer, SDL_Color colour);

    /// draw a single frame
    void draw(std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);

    void clearFromTextureMap(std::string);

    SDL_Texture* getTexture(std::string id)
    {
        return textureMap[id];
    }

    static  TextureManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
    }

private:
    TextureManager() {};
    static TextureManager* s_pInstance;

    int getRandom(int low, int high);
    std::random_device dev;

    void recolour(SDL_Surface* pSurface, SDL_Color colour);
};

typedef TextureManager TheTextureManager;

#endif //HELLOSDL_TEXTUREMANAGER_H
