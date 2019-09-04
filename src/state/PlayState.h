//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_PLAYSTATE_H
#define HELLOSDL_PLAYSTATE_H

#include <vector>
#include <random>
#include <thread>
#include "GameState.h"
#include "../entity/GameObject.h"
#include "../entity/SDLGameObject.h"
#include "../entity/ProjectileHandler.h"
#include "../entity/mob/Player.h"


class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    void doSomething(int i){std::cout << "thread works... i is "<< i << "\n";}

    void checkCollisions();

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    bool checkAlive(SDLGameObject* p);

    virtual std::string getStateID() const {return s_playID;}


    // TODO

    //void checkPlayerCollision()
    //{
    //    std::cout << "hello i was used\n";
    //} // a thread that checks all game objects for player collisions
    void checkEnemyBulletCollision() {} // a thread that check each bullet for enemy collisions

    // we want a projectile manager object not singleton
    // ...
    bool playerCollision = false; // our thread will
    // TODO

private:

    const int MAX_GAMEOBJECTS = 2000;

    int getRandom(int, int);
    void addEnemy();

    std::random_device dev;
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;

    GameObject* pPlayer;

    ProjectileHandler* pProjectileHandler;
};


#endif //HELLOSDL_PLAYSTATE_H
