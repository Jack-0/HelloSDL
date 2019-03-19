//
// Created by jack on 17/03/19.
//

#include "Player.h"

Player::Player(const LoaderParams *pParams)
: SDLGameObject(pParams)
{

}

void Player::update()
{
    //GameObject::update();
    //SDLGameObject::m_x -= 1;
    //m_x -= 1;
    moveRight();
}

void Player::draw()
{
    SDLGameObject::draw();
   // GameObject::draw(pRenderer);
}

/*
void Player::clean()
{
}
 */