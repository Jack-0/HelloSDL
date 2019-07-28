//
// Created by jack on 20/07/19.
//

#include "GameOverState.h"
#include "../Game.h"
#include "../entity/AnimatedGraphic.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState);
}

bool GameOverState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../res/menu/gameOver.png", "gameOver", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("../res/menu/menuBtn.png", "menuBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("../res/menu/restartBtn.png", "restartBtn", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    /*todo
    GameObject* gameOverText = new AnimatedGraphic(
            new LoaderParams((720 / 2) + 228, (450 / 2) - 80, 256, 100, "gameOver"), 2);
    GameObject* menuButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2) , 256, 100, "menuBtn"), s_gameOverToMain );
    GameObject* restartButton = new Button(
            new LoaderParams( (720 / 2) + 228, (450 / 2) + 200, 256, 100, "restartBtn"), s_restartPlay );
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(menuButton);
    m_gameObjects.push_back(restartButton);
    */

    std::cout << "Entering game over state\n";
    return true;

}

bool GameOverState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("gameOver");
    TheTextureManager::Instance()->clearFromTextureMap("menuBtn");
    TheTextureManager::Instance()->clearFromTextureMap("restartBtn");

    std::cout << "Exiting game over state\n";
    return true;
}

void GameOverState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void GameOverState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}
