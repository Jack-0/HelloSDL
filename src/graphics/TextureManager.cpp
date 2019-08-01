//
// Created by jack on 16/03/19.
//

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

void TextureManager::clearFromTextureMap(std::string id)
{
    textureMap.erase(id);
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* renderer)
{
    SDL_Surface* pTempSurface = IMG_Load(filename.c_str());
    if(!pTempSurface)
    {
        std::cout << "Error loading file \"" << filename << "\"" << std::endl;
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if(pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }

    std::cout << "Load: Something went wrong" << std::endl;
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int w, int h, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int w, int h, int row, int frame,
        SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = w * frame;
    srcRect.y = h * (row - 1);
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


