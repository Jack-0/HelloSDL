//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"

Game* Game::s_pInstance = 0; // singleton


bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{

    // create some game objects
    //m_gameObjects.push_back(new Enemy(new LoaderParams(-34,0,68, 128, "balloon"),120));
    //m_gameObjects.push_back(new Enemy(new LoaderParams(-34,200,68, 128, "balloon"),220));
    //m_gameObjects.push_back(new Enemy(new LoaderParams(-34,400,68, 128, "balloon"),150));
    //m_gameObjects.push_back(new Enemy(new LoaderParams(-34,600,68, 128, "balloon"),600));
    //m_gameObjects.push_back(new Player(new LoaderParams(-34,1000, 68, 128, "balloon")));



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

    // load textures into the texture manager
    load("g_balloon", "../res/greenBalloon.png");
    load("g_balloon_death", "../res/greenBalloonDeath.png");
    load("r_balloon", "../res/redBalloon.png");
    load("r_balloon_death", "../res/redBalloonDeath.png");
    load("b_balloon", "../res/blueBalloon.png");
    load("b_balloon_death", "../res/blueBalloonDeath.png");
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

int Game::getRandom(int low, int high)
{

    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(low, high);
    return rand(rng);
}


void Game::update()
{
    std::string balloonType = "";
    int type;
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
    m_gameObjects.push_back(new Enemy(new LoaderParams(-70,getRandom(-100,900),68, 128, balloonType),getRandom(0,720),type));

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

void Game::quit()
{
    running = false;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}