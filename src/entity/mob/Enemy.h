//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

#include "../SDLGameObject.h"
#include "../../input/InputHandler.h"
#include "../../factory/GameObjectFactory.h"
#include "../VanityItem.h"

static const int RED = 0;
static const int GREEN = 1;
static const int BLUE = 2;


class Enemy : public SDLGameObject
{
public:

    Enemy();
    Enemy(const LoaderParams* pParams);

    void operator() (LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

private:
    VanityItem tail = VanityItem();
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
