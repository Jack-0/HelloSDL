//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_PLAYER_H
#define HELLOSDL_PLAYER_H

#include "../SDLGameObject.h"
#include "../../input/InputHandler.h"
#include "../../factory/GameObjectFactory.h"
#include "../VanityItem.h"
#include "../ProjectileHandler.h"

class Player : public SDLGameObject
{
public:

    Player();

    void addProjectileManager(ProjectileHandler* pPh) {pProjectileHandler = pPh;}

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

private:
    VanityItem tail = VanityItem();
    VanityItem hat = VanityItem();

    Vector2D m_center = Vector2D(0,0);

    ProjectileHandler* pProjectileHandler;

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
