//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

#include "../SDLGameObject.h"
#include "../../input/InputHandler.h"
#include "../../factory/GameObjectFactory.h"

static const int RED = 0;
static const int GREEN = 1;
static const int BLUE = 2;


class Enemy : public SDLGameObject
{
public:

    Enemy();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

    void incrementAcceleration();

private:
    bool dead = false;
    int deathFrame = 0;
    int deathTime = 0;
    int ttd = 0;
    int max_ttd;
    int type;
    float acceleration = 0.005;

};

class EnemyCreator : public BaseCreator
{
public:
    GameObject* createGameObject() const
    {
        return new Enemy();
    }

};
#endif //HELLOSDL_ENEMY_H
