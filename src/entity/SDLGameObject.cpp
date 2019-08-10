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
    //m_frames = pParams->getNumFrames(); //todo implement this
}

void SDLGameObject::clean()
{
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_texutreID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

/*
void SDLGameObject::drawGiven(std::string texID, int frame)
{
    TextureManager::Instance()->drawFrame(texID, m_pos.getX(), m_pos.getY(), m_width, m_height, m_currentRow, frame, TheGame::Instance()->getRenderer());
}
 */

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_pos += m_velocity;
    m_currentFrame = int ((SDL_GetTicks() / 200) % m_numFrames);
    //animate();
}
