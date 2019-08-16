//
// Created by jack on 19/03/19.
//

#include "SDLGameObject.h"
#include "../Game.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}

void SDLGameObject::load(const LoaderParams *pParams)
{
    m_pos = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0, 0);

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_texutreID = pParams-> getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;
    m_numFrames = pParams->getNumFrames();

    rect.x = m_pos.getX();
    rect.y = m_pos.getY();
    rect.w = m_width;
    rect.h = m_height;
}

void SDLGameObject::clean()
{
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->draw(m_texutreID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_pos += m_velocity;
    // animate the frame
    m_currentFrame = int ((SDL_GetTicks() / m_animSpeed) % m_numFrames);

    rect.x = m_pos.getX();
    rect.y = m_pos.getY();
}
