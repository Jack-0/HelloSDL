//
// Created by jack on 30/09/19.
//

#ifndef HELLOSDL_TEXT_H
#define HELLOSDL_TEXT_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include "SDLGameObject.h"



class Text
{
public:
    Text(int x, int y, std::string msg);

    void draw();
    void update();
    void clean();

    void changeText(std::string new_text);
    void setX(int x) {m_x = x;}
    void setY(int y) {m_y = y;}


private:

    void generateTexture();

    std::string m_text;
    TTF_Font* pFont;
    SDL_Color m_colour;
    SDL_Surface* pSurface;
    SDL_Texture* pTexture;

    SDL_Rect rect;
    int m_textW;
    int m_textH;

    int m_x;
    int m_y;

};


#endif //HELLOSDL_TEXT_H
