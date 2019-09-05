//
// Created by jack on 31/05/19.
//

#include "PlayState.h"
#include "../graphics/TextureManager.h"
#include "../Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "../entity/ProjectileHandler.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

/**
 * Creates one enemy and adds it to game objects, note enemies are assigned random colours
 */
void PlayState::addEnemy(){
    std::string head_type = "";

    // randomly choose a balloon to spawn
    switch(getRandom(0,2))
    {
        case 0:
            head_type = "head_r";
            break;
        case 1:
            head_type = "head_g";
            break;
        case 2:
            head_type = "head_b";
            break;
    }
    // create and add balloon to game objects (balloon type based on the random balloon choice)
    auto SCREEN_HEIGHT = TheGame::Instance()->getScreenHeight();
    m_gameObjects.push_back(new Enemy(new LoaderParams(-70, getRandom(-10, SCREEN_HEIGHT -51) ,38, 52, head_type, 1)));
}

void PlayState::update()
{
    // if escape is pressed enter the pause state
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());

    // add a new balloon, if the maximum is not reached
    if(m_gameObjects.size() < MAX_GAMEOBJECTS)
        addEnemy();

    // update projectile handler
    pProjectileHandler->update();

    // update player
    pPlayer->update();

    // update all game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // check to see if the enemy is alive, if not remove it
        if(!checkAlive(static_cast<SDLGameObject*>(m_gameObjects[i])))
        {
            m_gameObjects[i]->clean();
            m_gameObjects.erase(m_gameObjects.begin() + i);
        }
        m_gameObjects[i]->update();
    }
}

void PlayState::render()
{
    if(!gameOver)
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
        pPlayer->draw();
        pProjectileHandler->draw();
    }
}

bool PlayState::onEnter()
{
    TheTextureManager::Instance()->load("../res/mob/head.png", "head", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/tail.png", "tail", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/hat.png", "hat", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/mob/projectile.png", "projectile", TheGame::Instance()->getRenderer());
    m_textureIDs.push_back("head");
    m_textureIDs.push_back("tail");
    m_textureIDs.push_back("hat");
    m_textureIDs.push_back("projectile");

    pPlayer = new Player();
    pPlayer->load(new LoaderParams(TheGame::Instance()->getScreenWidth()/2,TheGame::Instance()->getScreenHeight()/2,38,52,"head",1));

    // add projectile handler
    pProjectileHandler = new ProjectileHandler();
    // give the player a pointer to the projectile handler
    Player *pPlayer_cast = dynamic_cast<Player*>(pPlayer);
    pPlayer_cast->addProjectileManager(pProjectileHandler);

    //m_gameObjects.push_back(pPlayer);


    // generate colours for balloons.. note red is not pure red; green is not pure green; etc.
    SDL_Color red;
    SDL_Color green;
    SDL_Color blue;
    red.r = 200; red.g = 0; red.b = 120; red.a = 0;
    green.r = 0; green.g = 200; green.b = 120; green.a = 0;
    blue.r = 0; blue.g = 120; blue.b = 200; blue.a = 0;

    // Generate red green and blue textures from default pink head image
    m_textureIDs.push_back("head_r");
    m_textureIDs.push_back("head_g");
    m_textureIDs.push_back("head_b");
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_r", TheGame::Instance()->getRenderer(), red);
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_g", TheGame::Instance()->getRenderer(), green);
    TheTextureManager::Instance()->loadWithNewColour("../res/mob/head.png", "head_b", TheGame::Instance()->getRenderer(), blue);

    ///TheTextureManager::Instance()->loadWithNewColour("../res/mob/projectile.png", "blueProjectile", TheGame::Instance()->getRenderer(), blue);

    //std::thread playerColl_t();
    //std::thread bulletColl_t;
    /** TODO uneeded multi thread test
    LoaderParams params = LoaderParams(-70, getRandom(-10, screenHeight -51) ,38, 52, "head_y", 1);
    Enemy e =  Enemy(&params);
    std::thread threadObject (e, &params);
    threadObject.detach();
    */
    //std::thread t(&PlayState::doSomething, this, 10);
    //t.detach();

    std::thread collisionsThread(&PlayState::checkCollisions, this);
    collisionsThread.detach();

    // start projectile handler concurrency
    //std::thread projectileThread();
    //projectileThread.detach();#
    // need pointer to enemies
    // start player collision detection concurrency
    // need pointer to enemies
    std::cout << "Entering play state\n";
    return true;
}

void PlayState::checkCollisions()
{
    Player *cast = dynamic_cast<Player*>(pPlayer);

    // wait 300 ms for objects to initialise properly. Due to thread checking before full init
    SDL_Delay(300); // TODO could be a better way of checking that objects are initialised

    while(cast->alive())
    {
        if(!m_gameObjects.empty())
        {
            for(int i = 0; i <m_gameObjects.size(); i++)
            {
                // check player collisions
                if(checkCollision(static_cast<SDLGameObject*>(pPlayer), static_cast<SDLGameObject*>(m_gameObjects[i])))
                {
                    gameOver = true;
                    TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
                    cast->kill();
                }
                // check projectile collisions
                //if(m_gameObjects[i] != NULL)
                    pProjectileHandler->collision(static_cast<SDLGameObject*>(m_gameObjects[i]));
            }
        }
    }
}

bool PlayState::onExit()
{
    pProjectileHandler->clean();

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    for (int i = 0; i < m_textureIDs.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }

    pPlayer->clean();
    SDL_Delay(100);
    //TheProjectileHandler::Instance()->clean();
    std::cout << "Exiting play state\n";
    return true;
}

int PlayState::getRandom(int low, int high)
{
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(low, high);
    return rand(rng);
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2)
{
    int leftA, leftB, rightA, rightB;
    int topA, topB, bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();


    if(bottomA <= topB) {return false;}
    if(topA >= bottomB) {return false;}
    if(rightA <= leftB) {return false;}
    if(leftA >= rightB) {return false;}

    return true;
}

bool PlayState::checkAlive(SDLGameObject *p)
{
    return p->alive();
}
