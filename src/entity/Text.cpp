//
// Created by jack on 30/09/19.
//

#include "Text.h"
#include "../Game.h"

Text::Text(int x, int y, std::string msg)
{
    m_x = x;
    m_y = y;
    m_text = msg;

    TTF_Init();

    generateTexture();
}

void Text::generateTexture()
{
    pFont = TTF_OpenFont("../res/fonts/OpenSans-Regular.ttf", 24);
    m_colour = SDL_Color{0,0,0,0};

    pSurface = TTF_RenderText_Blended(pFont, m_text.c_str(), m_colour); // Blended used to remove jagged edges
    if(pSurface == NULL)
        std::cout << "TTF error\n";

    pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pSurface);
    if(pTexture == NULL)
        std::cout << "Text-to-texture Error\n";

    m_textW = pSurface->w;
    m_textH = pSurface->h;

    rect = SDL_Rect{m_x, m_y, m_textW , m_textH};

    SDL_FreeSurface(pSurface);
}

void Text::changeText(std::string new_text)
{
    m_text = new_text;
    generateTexture();
}

void Text::draw()
{
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), pTexture, NULL, &rect, 0, 0, SDL_FLIP_NONE);
}

void Text::update()
{
    //SDLGameObject::update();
}

void Text::clean()
{
    //SDLGameObject::clean();
}