//
// Created by jack on 05/06/19.
//

#include "PauseState.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PauseState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../res/resumeBtn.png", "resumeBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("../res/menuBtn.png", "menuBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* playButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2), 256, 100, "resumeBtn"), s_resumePlay );
    GameObject* exitButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2) + 200, 256, 100, "menuBtn"), s_pauseToMain );

    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(exitButton);
}

bool PauseState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("resumeBtn");
    TheTextureManager::Instance()->clearFromTextureMap("menuBtn");
    //TheInputHandler::Instance()->reset();

    return true;
}
