//
// Created by jack on 16/03/19.
//

#ifndef HELLOSDL_TEXTUREMANAGER_H
#define HELLOSDL_TEXTUREMANAGER_H

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/// A singleton that manages all game textures.

class TextureManager
{
public:
    std::map<std::string, SDL_Texture*> texturemMap;

    bool load(std::string, std::string, SDL_Renderer*);
    /// draw animation
    void draw(std::string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);
    /// draw a single frame
    void drawFrame(std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);

    void clearFromTextureMap(std::string);

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
};

typedef TextureManager TheTextureManager;

#endif //HELLOSDL_TEXTUREMANAGER_H
