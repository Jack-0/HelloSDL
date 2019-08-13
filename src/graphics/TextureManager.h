//
// Created by jack on 16/03/19.
//

#ifndef HELLOSDL_TEXTUREMANAGER_H
#define HELLOSDL_TEXTUREMANAGER_H

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * TheTextureManager is a singleton used to manage all in game textures.
 * Textures are loaded with this singleton.
 * Texture are drawn with this singleton.
 *
 * Note:
 * Textures can be loaded with colour modifications.
 */
class TextureManager
{
public:
    // a map that pairs a texture with an id
    std::map<std::string, SDL_Texture*> textureMap;

    // load an image and add it as a texture to the textureMap
    bool load(std::string filename, std::string id, SDL_Renderer* pRenderer);
    bool loadWithNewColour(std::string filename, std::string id,
            SDL_Renderer* pRenderer, SDL_Color colour);

    // draw to the screen
    void draw(std::string id, int x, int y, int w, int h, int row, int frame,
            SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // remove a texture from the textureMap
    void clearFromTextureMap(std::string id);

    // singleton
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
    // singleton
    static TextureManager* s_pInstance;

    // modify original texture colours to a new colour
    void recolour(SDL_Surface* pSurface, const SDL_Color colour);
    void recolourSection(Uint8* r, Uint8* g, Uint8* b, Uint8 imgR, Uint8 imgG, Uint8 imgB,
            const SDL_Color newColour, int depth);
};

typedef TextureManager TheTextureManager;

#endif //HELLOSDL_TEXTUREMANAGER_H
