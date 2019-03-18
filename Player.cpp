//
// Created by jack on 17/03/19.
//

#include "Player.h"

void Player::load(int x, int y, int w, int h, std::string id)
{
    GameObject::load(x,y,w,h,id);
}

void Player::update()
{
    //GameObject::update();
    m_x -= 1;
}

void Player::draw(SDL_Renderer *pRenderer)
{
    GameObject::draw(pRenderer);
}