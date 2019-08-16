//
// Created by jack on 17/03/19.
//

#include "Player.h"
#include "../ProjectileHandler.h"

Player::Player() : SDLGameObject()
{
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    tail.load(new LoaderParams((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height, 6, 51, "tail", 2));
    hat.load(new LoaderParams((m_pos.getX() + m_width / 2) - 9, m_pos.getY() - 14, 18, 16, "hat", 1));
}

void Player::update()
{
    // update center pos
    m_center = Vector2D(m_pos.getX() + m_width / 2 - 4, m_pos.getY() + 22);

    int speed = 2; // TODO this should be private (doesn't need to be generated on each update)

    // Old test code TODO remove this
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    //    std::cout << "Space!\n";

    // Reset movement
    setYvelocity(0);
    setXvelocity(0);

    // Detect movement and move the player
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
        setYvelocity(-speed);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
        setYvelocity(speed);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
        setXvelocity(-speed);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
        setXvelocity(speed);

    // fire projectile in direction of mouse TODO put in function? also improve this
    if(TheInputHandler::Instance()->getMouseButtonStates(LEFT))
    {
        Vector2D mousePos = Vector2D(TheInputHandler::Instance()->getMouseX(), TheInputHandler::Instance()->getMouseY());
        Vector2D direction = (mousePos - m_pos);
        direction.noramalise();
        direction *= 3;
        TheProjectileHandler::Instance()->fireProjectile(m_center, direction);
    }

    // update
    SDLGameObject::update();

    // update tail position
    tail.setPos((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height);
    tail.update();

    // update hat position
    hat.setPos((m_pos.getX() + m_width / 2) - 9, m_pos.getY() - 14);
    hat.update();
}

void Player::draw()
{
    SDLGameObject::draw();
    tail.draw();
    hat.draw();
}

void Player::clean()
{
    tail.clean();
    hat.clean();
    SDLGameObject::clean();
}
