//
// Created by jack on 16/03/19.
//

#ifndef HELLOSDL_TEXTUREMANAGER_H
#define HELLOSDL_TEXTUREMANAGER_H

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
public:
    std::map<std::string, SDL_Texture*> texturemMap;

    bool load(std::string, std::string, SDL_Renderer*);
    void draw(std::string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);
    void drawFrame(std::string, int, int, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);
};


#endif //HELLOSDL_TEXTUREMANAGER_H
