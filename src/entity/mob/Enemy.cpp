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
    m_velocity.setX(1);

    tail.load(new LoaderParams((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height, 6, 51, "tail", 2));
}

void Enemy::update()
{
    SDLGameObject::update();

    // update tail position
    tail.setPos((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height);
    tail.update();
}

void Enemy::draw()
{
    SDLGameObject::draw();

    tail.draw();
}

void Enemy::clean()
{
    SDLGameObject::clean();

    tail.clean();
}
