//
// Created by jack on 15/08/19.
//

#ifndef HELLOSDL_PROJECTILEHANDLER_H
#define HELLOSDL_PROJECTILEHANDLER_H


#include <vector>
#include "Projectile.h"

class ProjectileHandler
{
public:

    ProjectileHandler();

    void draw();
    void update();
    void clean();

    bool collision(SDLGameObject* enemy);
    //void checkForCollisions(std::vector<SDLGameObject*> gameObjects);

    // fire a single projectile
    void fireProjectile(Vector2D origin, Vector2D direction, float speed=3);
    // fire multiple projectiles out in a circular radius from a central position
    void fireNova(Vector2D origin);

private:

    bool checkProjectileEnemyCollision(SDLGameObject *p1, SDLGameObject *p2);

    std::vector<Projectile*> m_projectiles;
};

//typedef ProjectileHandler TheProjectileHandler;


#endif //HELLOSDL_PROJECTILEHANDLER_H
