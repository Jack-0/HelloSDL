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
    // exit if there is nothing to check against
    if(m_projectiles.empty())
        return false;
    if(p1 == nullptr)
        return false;

    for(int i = 0; i < m_projectiles.size(); i++)
    {
        if(m_projectiles[i] == nullptr || m_projectiles[i] == 0)
            return false;

        if(checkProjectileEnemyCollision(p1, m_projectiles[i]))
        {
            p1->kill();
            m_projectiles[i]->kill();
            return true;
        }
    }
    return false;
}

bool ProjectileHandler::checkProjectileEnemyCollision(SDLGameObject *p1, SDLGameObject *p2)
{
    int leftA, leftB, rightA, rightB;
    int topA, topB, bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    if(bottomA <= topB) {return false;}
    if(topA >= bottomB) {return false;}
    if(rightA <= leftB) {return false;}
    if(leftA >= rightB) {return false;}

    return true;
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




