//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_PLAYER_H
#define HELLOSDL_PLAYER_H

#include "../SDLGameObject.h"
#include "../../input/InputHandler.h"
#include "../../factory/GameObjectFactory.h"

class Player : public SDLGameObject
{
public:

    Player();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);
};

class PlayerCreator : public BaseCreator
{
public:
    GameObject* createGameObject() const
    {
        return new Player();
    }

};

#endif //HELLOSDL_PLAYER_H
