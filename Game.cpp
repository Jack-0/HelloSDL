//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{
    m_animSpeed = 60;

    /*
    m_player = new Player();
    m_gameObject1 = new GameObject();
    m_gameObject2 = new GameObject();
    m_gameObject3 = new GameObject();

    m_gameObjects.push_back(m_player);
    m_gameObjects.push_back(m_gameObject1);
    m_gameObjects.push_back(m_gameObject2);
    m_gameObjects.push_back(m_gameObject3);


    m_player->load(100,100, 256, 382, "tower1");
    m_gameObject1->load(720-100,450, 256, 382, "tower2");
    m_gameObject2->load(720-400,450, 256, 382, "tower2");
    m_gameObject3->load(720-700,450, 256, 382, "tower2");

    m_enemy = new Enemy();
    m_gameObjects.push_back(m_enemy);
    m_enemy->load(0,0,256,382,"tower3");

     */

    m_gameObjects.push_back(new Player(new LoaderParams(100,100, 256, 382, "tower1")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(900,100,256, 382, "tower3")));

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

    // load a texture
    // note image is one dir out then into res
    if(!TheTextureManager::Instance()->load("../res/tier_2.png","tower1", renderer))
    {
        std::cout << "Error with the texture manager" << std::endl;
        return false;
    }
    else
    {
        // success load more bad practice here but this is just me testing
        TheTextureManager::Instance()->load("../res/tier_3.png","tower2",renderer);
        TheTextureManager::Instance()->load("../res/tier_4_range.png","tower3",renderer);
    }


    running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    /// render start#
    /*
    TheTextureManager::Instance()->drawFrame("tower1",0,0,256,382,1, m_currentFrame, renderer);
    TheTextureManager::Instance()->drawFrame("tower2",256,0,256,382,1, m_currentFrame, renderer);
    TheTextureManager::Instance()->drawFrame("tower3",256 * 2,0,256,382,1, m_currentFrame, renderer);
     */
 //   player->draw(renderer);
 //   gameObject->draw(renderer);

    draw();
    /// render end
    SDL_RenderPresent(renderer);
}

void Game::draw()
{
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}


void Game::update()
{
    m_currentFrame = int (((SDL_GetTicks() / m_animSpeed ) % 8));
   // player->update();
   // gameObject->update();
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
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if(m_animSpeed <= 10)
                        break;
                    m_animSpeed -= 10;
                    std::cout << m_animSpeed << std::endl;
                }
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if(m_animSpeed >= 2000)
                        break;
                    m_animSpeed += 10;
                    std::cout << m_animSpeed << std::endl;
                }
                break;

            default:
                //std::cout << "Key \"" << event.type << "\" pressed..." << std::endl;
                break;
        }
    }
}

