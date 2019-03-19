//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

Enemy::Enemy(const LoaderParams *pParams)
: SDLGameObject(pParams)
{

}

void Enemy::update()
{
    //GameObject::update();
    //SDLGameObject::m_x -= 1;
    //m_x -= 1;
    //moveLeft();
}

void Enemy::draw()
{
    SDLGameObject::draw();
   // GameObject::draw(pRenderer);
}

/*
void Enemy::clean()
{
}
 */
