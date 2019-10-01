//
// Created by jack on 17/03/19.
//

#include "Player.h"
#include "../ProjectileHandler.h"

Player::Player() : SDLGameObject()
{
}

Player::Player(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    tail.load(new LoaderParams((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height, 6, 51, "tail", 2));
    hat.load(new LoaderParams((m_pos.getX() + m_width / 2) - 9, m_pos.getY() - 14, 18, 16, "hat", 1));
    m_speed = 2.0f;
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    tail.load(new LoaderParams((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height, 6, 51, "tail", 2));
    hat.load(new LoaderParams((m_pos.getX() + m_width / 2) - 9, m_pos.getY() - 14, 18, 16, "hat", 1));
    m_speed = 2.0f;
}

void Player::update()
{
    // update center pos
    m_center = Vector2D(m_pos.getX() + m_width / 2 - 4, m_pos.getY() + 22);

    // Reset movement
    setYvelocity(0);
    setXvelocity(0);

    // Detect movement and move the player
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
        if(m_pos.getY() > 0)
            setYvelocity(-m_speed);
        else
            setYvelocity(0);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
        if(m_pos.getY() + m_height < TheGame::Instance()->getScreenHeight())
            setYvelocity(m_speed);
        else
            setYvelocity(0);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
        if(m_pos.getX() > 0)
            setXvelocity(-m_speed);
        else
            setXvelocity(0);
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
        if(m_pos.getX() + m_width < TheGame::Instance()->getScreenWidth())
            setXvelocity(m_speed);
        else
            setXvelocity(0);

    // fire projectile in direction of mouse upon mouse click
    if(TheInputHandler::Instance()->getMouseButtonStates(LEFT))
    {
        Vector2D mousePos = Vector2D(TheInputHandler::Instance()->getMouseX(), TheInputHandler::Instance()->getMouseY());
        Vector2D direction = (mousePos - m_pos);
        pProjectileHandler->fireProjectile(m_center, direction);
    }

    // fire a nova blast upon pressing the 'N' key
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_N))
    {
        pProjectileHandler->fireNova(m_center);
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
