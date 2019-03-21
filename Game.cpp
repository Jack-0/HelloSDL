//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"

Game* Game::s_pInstance = 0; // singleton

bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{
    // create some game objects
    m_gameObjects.push_back(new Enemy(new LoaderParams(900,100,256, 382, "tower3")));
    m_gameObjects.push_back(new Player(new LoaderParams(100,100, 68, 128, "balloon")));
    m_gameObjects.push_back(new Player(new LoaderParams(100*2,100*2, 68, 128, "balloon")));
    m_gameObjects.push_back(new Player(new LoaderParams(100,100*3, 68, 128, "balloon")));
    m_gameObjects.push_back(new Player(new LoaderParams(0,100*4, 68, 128, "balloon")));

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
                SDL_SetRenderDrawColor(renderer, 0, 100, 100, 0);
            }
            else
                { return false; }
        } else
            { return false; }
    } else
        { return false; }

    // load textures into the texture manager
    load("balloon", "../res/balloonPerson.png");

    // game is now running
    running = true;
    return true;
}

void Game::load(std::string name, std::string path)
{
    if(!TheTextureManager::Instance()->load(path,name,renderer))
    {
        std::cout << "Error with the texture (\"" << name << "\", \"" << path << "\")" << std::endl;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    /// render start
    draw();
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
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void Game::clean()
{
    std::cout << "Cleaning game" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

