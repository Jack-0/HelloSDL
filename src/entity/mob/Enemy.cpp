//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    m_numFrames = pParams->getNumFrames();
    m_velocity.setY(2);
}

void Enemy::update()
{
    changeFrame(m_numFrames, 200);
    SDLGameObject::update();
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::clean()
{
    SDLGameObject::clean();
}
