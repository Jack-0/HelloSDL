//
// Created by jack on 15/08/19.
//

#include "ProjectileHandler.h"

ProjectileHandler* ProjectileHandler::s_pInstance = 0;

ProjectileHandler::ProjectileHandler()
{}

void ProjectileHandler::fireProjectile(Vector2D origin,Vector2D direction)
{
    m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
}

void ProjectileHandler::draw()
{
    for(int i = 0; i < m_projectiles.size(); i++)
        m_projectiles[i]->draw();
}

void ProjectileHandler::update()
{
    for(int i = 0; i < m_projectiles.size(); i++)
        m_projectiles[i]->update();
}




