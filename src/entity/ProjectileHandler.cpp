//
// Created by jack on 15/08/19.
//

#include "ProjectileHandler.h"
#include "../Game.h"

//ProjectileHandler* ProjectileHandler::s_pInstance = 0;

ProjectileHandler::ProjectileHandler()
{}

void ProjectileHandler::fireProjectile(Vector2D origin, Vector2D direction, float speed)
{
    direction.noramalise();
    direction *= speed;
    m_projectiles.push_back(new Projectile(new LoaderParams(origin.getX(), origin.getY(),9,9,"projectile",1), direction));
}

void ProjectileHandler::fireNova(Vector2D origin)
{
    Vector2D direction;
    float spacing = 0.2; // spacing between projectiles in nova blast
    // fire in all directions
    for(float i = -1; i < 1; i += spacing)
    {
        // down
        direction = Vector2D(i,1);
        fireProjectile(origin, direction);
        // up
        direction = Vector2D(i,-1);
        fireProjectile(origin, direction);
        // right
        direction = Vector2D(1,i);
        fireProjectile(origin, direction);
        // left
        direction = Vector2D(-1,i);
        fireProjectile(origin, direction);
    }
}

bool ProjectileHandler::collision(SDLGameObject *p1)
{
    if(m_projectiles.empty())
        return false;

    for(int i = 0; i < m_projectiles.size(); i++)
    {
        SDLGameObject* p2 = static_cast<SDLGameObject*>(m_projectiles[i]);

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

void ProjectileHandler::checkForCollisions(std::vector<SDLGameObject*> gameObjects)
{
    for(int i = 0; i < gameObjects.size(); i++)
    {
        for(int j = 0; j < m_projectiles.size(); i++)
        {
            SDLGameObject* pProjectile = dynamic_cast<SDLGameObject*>(m_projectiles[j]);

            SDL_Rect r1 = gameObjects[i]->getRect();
            SDL_Rect r2 = pProjectile->getRect();
            if(SDL_HasIntersection(&r1, &r2))
            {
                gameObjects[i]->kill();
                pProjectile->kill();
            }
        }
    }
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




