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

void TextureManager::recolour(SDL_Surface* pSurface, SDL_Color colour)
{

    /*
     * Balloon Head colours:
     *  edge #990099
     *  ...  #B300B3
     *  ...  #CC00CC
     *  ...  #E600E6
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


        // modify the colour value
        // TODO: use function calls to clean this code
        if(r == 0x99 && g == 0x00 && b == 0x99)
        {
            if(colour.r != 0)
                r = colour.r - 20 * 3;
            else
                r = colour.r;
            if(colour.g != 0)
                g = colour.g - 20 * 3;
            else
                g = colour.g;
            if(colour.b != 0)
                b = colour.b - 20 * 3;
            else
                b = colour.b;
        }
        else if(r == 0xB3 && g == 0x00 && b == 0xB3)
        {
            if(colour.r != 0)
                r = colour.r - 20 * 2;
            else
                r = colour.r;
            if(colour.g != 0)
                g = colour.g - 20 * 2;
            else
                g = colour.g;
            if(colour.b != 0)
                b = colour.b - 20 * 2;
            else
                b = colour.b;
        }
        else if(r == 0xCC && g == 0x00 && b == 0xCC)
        {
            if(colour.r != 0)
                r = colour.r - 20 * 1;
            else
                r = colour.r;
            if(colour.g != 0)
                g = colour.g - 20 * 1;
            else
                g = colour.g;
            if(colour.b != 0)
                b = colour.b - 20 * 1;
            else
                b = colour.b;
        }
        else if(r == 0xE6 && g == 0x00 && b == 0xE6)
        {
            r = colour.r;
            g = colour.g;
            b = colour.b;
        }

        // recolour the index pixel
        *pixel = SDL_MapRGBA(pSurface->format, r, g, b, a);
    }
}

int TextureManager::getRandom(int low, int high)
{
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(low, high);
    return rand(rng);
}

