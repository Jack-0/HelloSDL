//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

//#import "GameObject.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:

    Enemy(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    //virtual void clean();
};


#endif //HELLOSDL_ENEMY_H
