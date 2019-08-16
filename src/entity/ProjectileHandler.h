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

    static ProjectileHandler* Instance()
    {
        if(s_pInstance == 0)
            s_pInstance = new ProjectileHandler();

        return s_pInstance;
    }


    void draw();
    void update();
    void clean();

    bool collision(SDLGameObject* gameObject);
    void fireProjectile(Vector2D origin, Vector2D direction);

private:

    ProjectileHandler();

    static ProjectileHandler* s_pInstance;

    std::vector<Projectile*> m_projectiles;
};

typedef ProjectileHandler TheProjectileHandler;


#endif //HELLOSDL_PROJECTILEHANDLER_H
