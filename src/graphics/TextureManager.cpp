//
// Created by jack on 16/03/19.
//

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

/**
 * Removes a texture from the texture map
 * @param id string of the texture to remove
 */
void TextureManager::clearFromTextureMap(std::string id)
{
    textureMap.erase(id);
}

/**
 * Loads a image file, then creates a texture that is added to TheTextureManager.
 * @param filename the image file to load
 * @param id the texture id
 * @param pRenderer a pointer to the renderer
 * @return boolean success
 */
bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pSurface = IMG_Load(filename.c_str());
    
    if(!pSurface)
    {
        std::cout << "Error loading file \"" << filename << "\"" << std::endl;
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    if(pTexture != 0)
    {
        textureMap[id] = pTexture;
        return true;
    }
    return false;
}

/**
 * Loads an image file, then creates a texture that is added to TheTextureManager.
 * However the texture will also be recoloured with SDL_Color colour.
 * @param filename the image file to load
 * @param id the texture id
 * @param pRenderer a pointer to the renderer
 * @param colour the colour the texture will be
 * @return boolean success
 */
bool TextureManager::loadWithNewColour(std::string filename, std::string id, SDL_Renderer *pRenderer, SDL_Color colour)
{
SDL_Surface* pSurface = IMG_Load(filename.c_str());

    if(!pSurface)
    {
        std::cout << "Error loading file \"" << filename << "\"" << std::endl;
        return false;
    }

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

/**
 * Draws a texture to the screen
 * @param id string of the texture
 * @param x pos
 * @param y pos
 * @param w width
 * @param h height
 * @param row in the texture/sprite sheet
 * @param frame in the texture/sprite sheet
 * @param pRenderer a pointer to the SDL_Renderer
 * @param flip SDL_RendererFlip
 */
void TextureManager::draw(std::string id, int x, int y, int w, int h, int row, int frame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = w * frame;
    srcRect.y = h * (row - 1);
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

/**
 * Takes a surface and looks for certain colours.
 * Those colours are then recoloured with the desired new colour.
 * @param pSurface pointer to SDL_Surface to be modified
 * @param colour SDL_Colour to change the original colour to
 */
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

/**
 * Used with TextureManager::recolour(...); This method modifies some r,g,b values to new r,g,b values.
 * It also applies a depth that is used to shade a texture.. the deeper the depth the darker the colour.
 * @param r pointer to the red value to modify
 * @param g pointer to the green value to modify
 * @param b pointer to the blue value to modify
 * @param imgR the red value to find and replace with newColour
 * @param imgG the green value to find and replace with newColour
 * @param imgB the blue value to find and replace with newColour
 * @param newColour SDL_Colour value that is used to repaint pointers to r,g,b
 * @param depth how dark the colour will be the higher the value the darker
 */
void TextureManager::recolourSection(Uint8* r, Uint8* g, Uint8* b, Uint8 imgR, Uint8 imgG, Uint8 imgB, const SDL_Color newColour, int depth)
{
    // TODO depth needs testing, too high a value may cause weird colouring behaviour
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

