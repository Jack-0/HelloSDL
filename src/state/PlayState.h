//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_PLAYSTATE_H
#define HELLOSDL_PLAYSTATE_H

#include <vector>
#include <random>
#include "GameState.h"
#include "../entity/GameObject.h"
#include "../entity/SDLGameObject.h"


class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    bool checkAlive(SDLGameObject* p);

    virtual std::string getStateID() const {return s_playID;}

private:

    const int MAX_GAMEOBJECTS = 20;

    int getRandom(int, int);
    void addEnemy();

    std::random_device dev;
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};


#endif //HELLOSDL_PLAYSTATE_H
