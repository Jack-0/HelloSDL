//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

void Enemy::update()
{
    m_y += 1;
    m_x += 1;
    m_currentFrame = int ((SDL_GetTicks() / 100) % 8);
}