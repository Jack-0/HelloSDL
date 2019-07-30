//
// Created by jack on 05/06/19.
//

#include "PauseState.h"
#include "../Game.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
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
    // parse the state
    StateParser stateParser;
    stateParser.parseState("../res/xml/test.xml", s_pauseID, &m_gameObjects, &m_textureIDs);
    m_callbacks.push_back(0); // to start from 1...
    m_callbacks.push_back(s_resumePlay);
    m_callbacks.push_back(s_pauseToMain);

    // set the callbacks from menu items
    setCallbacks(m_callbacks);

    std::cout << "entering pause state\n";
    return true;

    std::cout << "in pause state\n";
    /* todo
    GameObject* playButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2), 256, 100, "resumeBtn"), s_resumePlay );
    GameObject* exitButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2) + 200, 256, 100, "menuBtn"), s_pauseToMain );

    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(exitButton);
     */
}
void PauseState::setCallbacks(const std::vector<MenuState::Callback> &callbacks)
{
    // go through game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // if they are type button then set callback
        if(dynamic_cast<Button*>(m_gameObjects[i]))
        {
            Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
            pButton->setCallBack(callbacks[pButton->getCallbackID()]);
        }
    }
}

bool PauseState::onExit()
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

    std::cout << "Exiting pause state\n";
    return true;

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    //end = true;

    TheTextureManager::Instance()->clearFromTextureMap("resumeBtn");
    TheTextureManager::Instance()->clearFromTextureMap("menuBtn");
    TheInputHandler::Instance()->reset();

    return true;
}
