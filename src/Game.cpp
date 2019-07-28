//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"

Game* Game::s_pInstance = 0; // singleton


bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{
    // initialise SDL
    if(SDL_INIT_EVERYTHING >= 0)
    {
        std::cout << "SDL initialisation successful" << std::endl;
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if(window != 0)
        {
            std::cout << "Window initialisation successful" << std::endl;
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer != 0)
            {
                std::cout << "Renderer initialisation successful" << std::endl;
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
            }
            else
                { return false; }
        } else
            { return false; }
    } else
        { return false; }


    // TODO
    TheGameObjectFactory::Instance()->registerType("MenuButton", new ButtonCreator());

    // Game state
    m_pGameStateMachine = new GameStateMachine();
    //m_pGameStateMachine->changeState(new MenuState()); // todo

    // game is now running
    running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    /// render start
    m_pGameStateMachine->render();
    /// render end
    SDL_RenderPresent(renderer);
}

void Game::draw()
{
    // draw all game objects
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}





void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::clean()
{
    std::cout << "Cleaning game" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::quit()
{
    running = false;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}