//
// Created by jack on 31/05/19.
//

#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../res/playBtn.png", "playBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("../res/exitBtn.png", "exitBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* playButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2), 256, 100, "playBtn"), s_menuToPlay );
    GameObject* exitButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2) + 200, 256, 100, "exitBtn"), s_exitFromMenu );

    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(exitButton);

    std::cout << "Entering menu state\n";
    return true;
}

bool MenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playBtn");
    TheTextureManager::Instance()->clearFromTextureMap("exitBtn");

    std::cout << "Exiting menu state\n";
    return true;
}

void MenuState::s_menuToPlay()
{
    std::cout << "Play btn clicked!\n";
}

void MenuState::s_exitFromMenu()
{
    std::cout << "Exit btn clicked!\n";
}


