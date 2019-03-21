//
// Created by jack on 19/03/19.
//

#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams)
: GameObject(pParams), m_pos(pParams->getX(), pParams->getY())
{
    //m_x = pParams->getX();
    //m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_texutreID = pParams-> getTextureID();

    m_currentFrame = 1;
    m_currentRow = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_texutreID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}


void SDLGameObject::moveRight()
{
    m_pos.setX(m_pos.getX() + 1 );
}

void SDLGameObject::changeFrame()
{
    m_currentFrame = int ((SDL_GetTicks() / 100) % 8);
}

void SDLGameObject::update()
{
    m_currentFrame = int ((SDL_GetTicks() / 100) % 8);
}
