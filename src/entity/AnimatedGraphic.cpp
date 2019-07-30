//
// Created by jack on 20/07/19.
//

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic()
{
}

void AnimatedGraphic::load(const LoaderParams *pParams) 
{
    SDLGameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int (((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}