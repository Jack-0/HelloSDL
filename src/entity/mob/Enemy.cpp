//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{
}

void Enemy::load(const LoaderParams *pParams, int max, int eType)
{
    SDLGameObject::load(pParams);
    max_ttd = max;
    type = eType;
}

void Enemy::incrementAcceleration()
{
    acceleration += 0.005;
}

void Enemy::update()
{
    // TODO test code left click kills red, middle click kills green, right click kills blue
    if(TheInputHandler::Instance()->getMouseButtonStates(LEFT) && type == RED)
        dead = true;
    if(TheInputHandler::Instance()->getMouseButtonStates(MIDDLE) && type == GREEN)
        dead = true;
    if(TheInputHandler::Instance()->getMouseButtonStates(RIGHT) && type == BLUE)
        dead = true;


    // if the Enemy is not dead accelerate right, else accelerate down
    if(!dead)
        setXacceleration(acceleration);
    else
        setYacceleration(0.2);

    SDLGameObject::update(); // This must be called to use vector logic

    changeFrame(4, 200);
    ttd += 1; // increase time to die value

    // if it's time to die, then die (enemies currently only live for specified max_ttd)
    if(ttd >= max_ttd)
    {
        dead = true;
        return;
    }

}

void Enemy::draw()
{
    // if dead, render the death frames at a set speed, else render the move animation
    if(dead)
    {
        if(deathTime > 20)
        {
            setAlive(false);
            return;
        }

        switch(type)
        {
            case RED:
                SDLGameObject::drawGiven("r_balloon_death", deathFrame);
                break;
            case GREEN:
                SDLGameObject::drawGiven("g_balloon_death", deathFrame);
                break;
            case BLUE:
                SDLGameObject::drawGiven("b_balloon_death", deathFrame);
                break;
        }

        if(deathTime % 5 == 0)
            deathFrame++;
        deathTime +=1;
    }
    else
        SDLGameObject::draw();
}

void Enemy::clean()
{
    SDLGameObject::clean();
}
