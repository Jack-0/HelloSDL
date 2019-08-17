//
// Created by jack on 15/08/19.
//

#include "ProjectileHandler.h"
#include "../Game.h"

ProjectileHandler* ProjectileHandler::s_pInstance = 0;

ProjectileHandler::ProjectileHandler()
{}

void ProjectileHandler::fireProjectile(Vector2D origin, Vector2D direction)
{
    m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
}

void ProjectileHandler::fireNova(Vector2D origin)
{
    for(float i = -1; i <= 1; i+= 0.2)
    {
        Vector2D direction = Vector2D(i,1);
        m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
        direction = Vector2D(i,-1);
        m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
        direction = Vector2D(1,i);
        m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
        direction = Vector2D(-1,i);
        m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
    }
}

bool ProjectileHandler::collision(SDLGameObject *p1)
{
    for(int i = 0; i < m_projectiles.size(); i++)
    {
        SDLGameObject* p2 = dynamic_cast<SDLGameObject*>(m_projectiles[i]);

        SDL_Rect r1 = p1->getRect();
        SDL_Rect r2 = p2->getRect();
        if(SDL_HasIntersection(&r1, &r2))
        {
            p1->kill();
            p2->kill();
            return true;
        }
    }
    return false;
}

void ProjectileHandler::draw()
{
    for(int i = 0; i < m_projectiles.size(); i++)
        m_projectiles[i]->draw();
}

void ProjectileHandler::update()
{
    for(int i = 0; i < m_projectiles.size(); i++)
    {
        m_projectiles[i]->update();

        // clean and erase projectiles that are off the screen
        if(m_projectiles[i]->getPos().getY() < 0
        || m_projectiles[i]->getPos().getX() < 0
        || m_projectiles[i]->getPos().getY() > TheGame::Instance()->getScreenHeight()
        || m_projectiles[i]->getPos().getX() > TheGame::Instance()->getScreenWidth()
        || !m_projectiles[i]->alive())
        {
            m_projectiles[i]->clean();
            m_projectiles.erase(m_projectiles.begin() + i);
        }
    }
    //std::cout << "total projectiles = " << m_projectiles.size() << "\n";
}

void ProjectileHandler::clean()
{
    for(int i = 0; i < m_projectiles.size(); i++)
    {
        m_projectiles[i]->clean();
        m_projectiles.erase(m_projectiles.begin() + i);
    }

    m_projectiles.clear();

}




