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
#include "../entity/Text.h"

/**
 * This GameState represents the core game.
 * When this state is active;
 *  A player is spawned
 *  Enemies spawn on the left of the screen and float right
 *  The player can shoot down enemy balloons or die via collision
 */
class PlayState : public GameState
{
public:

    virtual void update();
    virtual void render();
    // init and clean
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_playID;}

private:

    const int MAX_GAMEOBJECTS = 2000; // MAXIMUM allowed game objects
    static const std::string s_playID;

    // a separate thread that is used to do all collisions checks in parallel with the game loop
    std::thread m_collisionThread;

    // checks collisions between projectiles, enemies and the player
    void checkAllCollisions(); // this function is threaded for performance
    bool checkPlayerEnemyCollision(SDLGameObject *enemy);

    // simple check to see if an SDLGameObject is alive
    bool checkAlive(SDLGameObject* p);

    // initialise textures
    void initTextures();

    // adds a new enemy to the game (with a random coloured spite)
    void addEnemy();

    // a boolean used to determine game state set to true when the collision thread detects a player to enemy collision
    bool gameOver = false;

    // a vector of enemies
    std::vector<GameObject*> m_gameObjects;

    // pointer to the player
    GameObject* pPlayer;

    // pointer to a projectile handler
    ProjectileHandler* pProjectileHandler;

    // render the score as text
    Text* scoreText;
    int score = 0;
};


#endif //HELLOSDL_PLAYSTATE_H
