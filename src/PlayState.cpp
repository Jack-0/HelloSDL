//
// Created by jack on 31/05/19.
//

#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PauseState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

/**
 * Creates one balloon and adds it to game objects, note the balloon has random properties
 */
void PlayState::createAndAddBalloon()
{
    std::string balloonType = "";
    int type;
    // randomly choose a balloon to spawn
    switch(getRandom(0,2))
    {
        case 0:
            balloonType = "r_balloon";
            type = 0;
            break;
        case 1:
            balloonType = "g_balloon";
            type = 1;
            break;
        case 2:
            balloonType = "b_balloon";
            type = 2;
            break;
    }
    // create and add balloon to game objects (balloon type based on the random balloon choice)
    m_gameObjects.push_back(new Enemy(new LoaderParams(-70,getRandom(-100,900),68, 128, balloonType),getRandom(0,720),type));
}

void PlayState::update()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }


    // add a new balloon
    createAndAddBalloon();

    // update all game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // TODO test if the object is a balloon with a cast
        if (dynamic_cast<const Enemy*> (m_gameObjects[i]))
        {
            //std::cout<<"\tobject is an enemy\n";
        }
        // TODO end test
        m_gameObjects[i]->update();
    }

    std::cout << "total objects = " << m_gameObjects.size() << "\n";
}

void PlayState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    // load textures into the texture manager
    TheTextureManager::Instance()->load("../res/playerBalloon.png", "p_balloon", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/greenBalloonDeath.png", "g_balloon_death", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/blueBalloon.png", "b_balloon", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/blueBalloonDeath.png", "b_balloon_death", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/redBalloon.png", "r_balloon", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/redBalloonDeath.png", "r_balloon_death", TheGame::Instance()->getRenderer());
    TheTextureManager::Instance()->load("../res/greenBalloon.png", "g_balloon", TheGame::Instance()->getRenderer());

    // create a player
    m_gameObjects.push_back(new Player(new LoaderParams(720 - 68 / 2, 450 - 128 / 2,68,128,"p_balloon")));

    return true;
}

bool PlayState::onExit()
{
    std::cout << "exiting play state \n";
    return true;
}

int PlayState::getRandom(int low, int high)
{
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(low, high);
    return rand(rng);
}
