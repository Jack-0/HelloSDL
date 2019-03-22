//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

Enemy::Enemy(const LoaderParams *pParams, int max, int type)
: SDLGameObject(pParams), max_ttd(max), type(type)
{

}

void Enemy::update()
{
    // if the Enemy is not dead accelerate right, else accelerate down
    if(!dead)
        setXacceleration(0.005);
    else
        setYacceleration(0.2);

    SDLGameObject::update(); // This must be called to use vector logic

    changeFrame(4, 200);
    ttd += 1; // increase time to die value

    // if it's time to die, then die
    if(ttd >= max_ttd)
    {
        dead = true;
        return;
    }
}

void Enemy::draw()
{
    // if dead render the death frames at a set speed, else render the move animation
    if(dead)
    {
        if(deathTime > 40)
            return;

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

        if(deathTime % 10 == 0)
            deathFrame++;
        deathTime +=1;
    }
    else
        SDLGameObject::draw();
}

/*
void Player::clean()
{
}
*/