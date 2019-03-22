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
    //changeFrame(4,50);
}

void Player::draw()
{
    SDLGameObject::draw();
}

/*
void Player::clean()
{
}
*/