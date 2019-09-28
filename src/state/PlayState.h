//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_PLAYSTATE_H
#define HELLOSDL_PLAYSTATE_H

#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include "GameState.h"
#include "PauseState.h"
#include "StateParser.h"
#include "GameOverState.h"
#include "../Game.h"
#include "../entity/GameObject.h"
#include "../entity/SDLGameObject.h"
#include "../entity/ProjectileHandler.h"
#include "../entity/mob/Player.h"
#include "../graphics/TextureManager.h"


class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    // init and clean
    virtual bool onEnter();
    virtual bool onExit();

    // checks collisions between projectiles, enemies and the player (threaded for performance)
    void checkCollisions();

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
    bool checkAlive(SDLGameObject* p);

    virtual std::string getStateID() const {return s_playID;}

private:

    const int MAX_GAMEOBJECTS = 2000;
    static const std::string s_playID;

    // returns a random number in the range low - high
    int getRandom(int low, int high);
    std::random_device dev;

    // adds a new enemy to the game (with a random coloured spite)
    void addEnemy();

    // initialise textures
    void initTextures();

    // game state (shared between main thread and collision thread, to communicate game state to renderer)
    bool gameOver = false;

    bool threadInit = false;

    // a vector of enemies
    std::vector<GameObject*> m_gameObjects;
    // pointer to the player
    GameObject* pPlayer;
    // pointer to a projectile handler
    ProjectileHandler* pProjectileHandler;
};


#endif //HELLOSDL_PLAYSTATE_H
