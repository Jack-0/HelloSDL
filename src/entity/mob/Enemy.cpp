//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

void Enemy::operator()(LoaderParams *pParams)
{
    load(pParams);

    Uint32 timeout = SDL_GetTicks() + 10;
    Uint32 draw_timeout = SDL_GetTicks() + 1;

    while(m_alive)
    {
        //SDL_Delay(10);
        std::cout << "I'm alive\n";
        // if x ticks have passed update
        if(SDL_GetTicks() > timeout)
        {
            update();
            timeout = SDL_GetTicks() + 10;
        }

        if(SDL_GetTicks() > draw_timeout)
        {
            draw();
            draw_timeout = SDL_GetTicks() + 1;
        }
    }
    std::cout << "I'm dead\n";
    clean();
}

Enemy::Enemy() : SDLGameObject()
{
}

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject()
{
    load(pParams);
}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    m_numFrames = pParams->getNumFrames();
    m_velocity.setX(m_speed);

    tail.load(new LoaderParams((m_pos.getX() + m_width / 2) - 3, m_pos.getY() + m_height, 6, 51, "tail", 2));
}

void Enemy::update()
{
    SDLGameObject::update();

    if(m_pos.getX() > TheGame::Instance()->getScreenWidth())
        m_alive = false;

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

