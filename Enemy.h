//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:

    Enemy(const LoaderParams* pParams, int max);

    virtual void draw();
    virtual void update();
    //virtual void clean();


private:
    bool dead = false;
    int deathFrame = 0;
    int deathTime = 0;
    int ttd = 0;
    int max_ttd;

};

#endif //HELLOSDL_ENEMY_H
