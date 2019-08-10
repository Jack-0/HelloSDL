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
    
    SDL_Surface* pSurface = IMG_Load(filename.c_str());
    
    if(!pSurface)
    {
        std::cout << "Error loading file \"" << filename << "\"" << std::endl;
        return false;
    }

    // todo Change pixel colours before creating the texture
    for(int i = 0; i < pSurface->w * pSurface->h; i++)
    {
        Uint8 r,g,b,a;
        Uint32* pixel = (Uint32 *) pSurface->pixels + i;
        SDL_GetRGBA(*pixel, pSurface->format, &r, &g, &b, &a);
        //std::cout << "r=" << (int) r << " g=" << (int) g << " b=" << (int) b << "\n";
        if(r == 0xFF && g == 0 && b == 0xFF)
        {
            r = 200; g = 0; b = 0;
        }
        else if(g == 0xEE)
        {
                r = 255; g = 0 ; b = 0;
        }
        *pixel = SDL_MapRGBA(pSurface->format, r, g, b, a);
    }
    // todo end test

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
    SDL_FreeSurface(pSurface);

    if(pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }
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


