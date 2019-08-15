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
    m_gameObjects.push_back(new Enemy(new LoaderParams(-70, getRandom(-100,900) ,38, 52, head_type, 1)));
}

void PlayState::update()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    // add a new balloon
    if(m_gameObjects.size() < MAX_GAMEOBJECTS)
        addEnemy();

    // update all game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // if it is not the player
        if(i != 0)
        {
            if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[i])))
            {
                TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
            }

            if(!checkAlive(dynamic_cast<SDLGameObject*>(m_gameObjects[i])))
            {
                m_gameObjects[i]->clean();
                m_gameObjects.erase(m_gameObjects.begin() + i);
            }
        }
        m_gameObjects[i]->update();
    }

    TheProjectileHandler::Instance()->update();
    //std::cout << "total objects = " << m_gameObjects.size() << "\n";
}

void PlayState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
    TheProjectileHandler::Instance()->draw();
}

bool PlayState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("../res/xml/test.xml", s_playID, &m_gameObjects, &m_textureIDs);

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

    std::cout << "Entering play state\n";
    return true;
}

bool PlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    for (int i = 0; i < m_textureIDs.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }

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
