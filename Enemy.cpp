//
// Created by jack on 18/03/19.
//

#include "Enemy.h"

Enemy::Enemy(const LoaderParams *pParams, int max)
: SDLGameObject(pParams), max_ttd(max)
{

}

void Enemy::update()
{
    changeFrame(4, 200);
    ttd += 1;

    if(ttd >= max_ttd)
    {
        dead = true;
        return;
    }

    moveRight();
}

void Enemy::draw()
{
    if(dead)
    {
        if(deathTime > 40)
            return;
        SDLGameObject::drawGiven("balloon_death", deathFrame);
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
