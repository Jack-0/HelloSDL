//
// Created by jack on 15/08/19.
//

#ifndef HELLOSDL_PROJECTILE_H
#define HELLOSDL_PROJECTILE_H


#include "SDLGameObject.h"

class Projectile : SDLGameObject
{
public:

    Projectile(const LoaderParams* pParams, Vector2D direction);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

private:
    Vector2D m_vector;
};


#endif //HELLOSDL_PROJECTILE_H
