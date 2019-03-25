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

    //if(TheInputHandler::Instance()->getMouseButtonStates(LEFT))
    //    std::cout << "Hello\n";
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