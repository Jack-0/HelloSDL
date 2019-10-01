//
// Created by jack on 30/09/19.
//

#include "Text.h"
#include "../Game.h"

Text::Text(int x, int y, std::string msg)
{
    m_x = x;
    m_y = y;
    m_msg = msg;

    TTF_Init();
    generateTexture();
}

void Text::generateTexture()
{
    pFont = TTF_OpenFont("../res/fonts/OpenSans-Regular.ttf", 24);
    m_colour = SDL_Color{0,0,0,0};

    // create a surface (using blended rendering)
    pSurface = TTF_RenderText_Blended(pFont, m_msg.c_str(), m_colour); // TTF_..._Blended used to remove jagged edges
    if(pSurface == NULL)
        std::cout << "TTF error\n";

    // create a texture
    pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pSurface);
    if(pTexture == NULL)
        std::cout << "Text-to-texture Error\n";

    // assign width and height to the height and length of the message rendered as a font
    m_textW = pSurface->w;
    m_textH = pSurface->h;

    rect = SDL_Rect{m_x, m_y, m_textW , m_textH};

    SDL_FreeSurface(pSurface);
}

void Text::changeText(std::string new_text)
{
    // change message value
    m_msg = new_text;
    // regenerate texture (due to updated msg)
    generateTexture();
}

void Text::draw()
{
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), pTexture, NULL, &rect, 0, 0, SDL_FLIP_NONE);
}

void Text::update()
{
}

void Text::clean()
{
}