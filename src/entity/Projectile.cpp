//
// Created by jack on 15/08/19.
//

#include "Projectile.h"

Projectile::Projectile(const LoaderParams *pParams, Vector2D direction)
: m_vector(direction)
{
    SDLGameObject();
    load(pParams);
}

void Projectile::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Projectile::draw()
{
    SDLGameObject::draw();
}



void Projectile::clean()
{
    SDLGameObject::clean();
}


void Projectile::update()
{
    m_velocity.setX(m_vector.getX());
    m_velocity.setY(m_vector.getY());
    SDLGameObject::update();
}
