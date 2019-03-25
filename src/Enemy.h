//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

#include "SDLGameObject.h"
#include "InputHandler.h"

static const int RED = 0;
static const int GREEN = 1;
static const int BLUE = 2;


class Enemy : public SDLGameObject
{
public:

    Enemy(const LoaderParams* pParams, int max, int type);

    virtual void draw();
    virtual void update();
    //virtual void clean();


private:
    bool dead = false;
    int deathFrame = 0;
    int deathTime = 0;
    int ttd = 0;
    int max_ttd;
    int type;

};

#endif //HELLOSDL_ENEMY_H
