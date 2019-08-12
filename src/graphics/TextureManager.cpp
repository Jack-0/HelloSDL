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

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
    SDL_FreeSurface(pSurface);

    if(pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }
    return false;
}


bool TextureManager::loadWithNewColour(std::string filename, std::string id, SDL_Renderer *pRenderer, SDL_Color colour)
{
SDL_Surface* pSurface = IMG_Load(filename.c_str());

    if(!pSurface)
    {
        std::cout << "Error loading file \"" << filename << "\"" << std::endl;
        return false;
    }

    // recolour certain surfaces
    //if(id == "head")
    recolour(pSurface, colour);

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    if(pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }
    return false;
}


void TextureManager::draw(std::string id, int x, int y, int w, int h, int row, int frame,
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


void TextureManager::recolour(SDL_Surface* pSurface, const SDL_Color colour)
{
    /*
     * Balloon Head colours are:
     *  edge #990099
     *  ...  #B300B3
     *  ...  #CC00CC
     *  ...  #E600E6
     *
     *      we use recolour to change these shades of pink to any colour we desire
     */

    // for each pixel in the surface
    for(int i = 0; i < pSurface->w * pSurface->h; i++)
    {
        // variables for red, green, blue and alpha and the new rgb
        Uint8 r,g,b,a;
        // pointer to the indexed pixel
        Uint32* pixel = (Uint32 *) pSurface->pixels + i;
        // fill r,g,b,a vars with values
        SDL_GetRGBA(*pixel, pSurface->format, &r, &g, &b, &a);
        // recolour a colour in the texture a new colour if it is a certain colour
        recolourSection(&r, &g, &b, 0x99, 0x00, 0x99, colour, 3);
        recolourSection(&r, &g, &b, 0xB3, 0x00, 0xB3, colour, 2);
        recolourSection(&r, &g, &b, 0xCC, 0x00, 0xCC, colour, 1);
        recolourSection(&r, &g, &b, 0xE6, 0x00, 0xE6, colour, 0);
        // recolour the index pixel
        *pixel = SDL_MapRGBA(pSurface->format, r, g, b, a);
    }
}


void TextureManager::recolourSection(Uint8* r, Uint8* g, Uint8* b, Uint8 imgR, Uint8 imgG, Uint8 imgB, const SDL_Color newColour, int depth)
{
    if(*r == imgR && *g == imgG && *b == imgB)
    {
        if(newColour.r != 0)
            *r = newColour.r - 20 * depth;
        else
            *r = newColour.r;
        if(newColour.g != 0)
            *g = newColour.g - 20 * depth;
        else
            *g = newColour.g;
        if(newColour.b != 0)
            *b = newColour.b - 20 * depth;
        else
            *b = newColour.b;
    }
}

