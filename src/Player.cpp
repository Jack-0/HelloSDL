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
    // update the players animation
    changeFrame(4,200);

    // Old test code TODO remove this
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    //    std::cout << "Space!\n";

    // Reset movement
    setYvelocity(0);
    setXvelocity(0);

    // Detect movement and move the player
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
        setYvelocity(-2);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
        setYvelocity(2);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
        setXvelocity(-2);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
        setXvelocity(2);

    // update
    SDLGameObject::update();
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