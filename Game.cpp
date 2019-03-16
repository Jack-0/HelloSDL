//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"


bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{
    m_animSpeed = 60;

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
    // render start
    //TheTextureManager::Instance()->draw("tower",0,0,256,382,renderer);
    TheTextureManager::Instance()->drawFrame("tower1",0,0,256,382,1, m_currentFrame, renderer);
    TheTextureManager::Instance()->drawFrame("tower2",256,0,256,382,1, m_currentFrame, renderer);
    TheTextureManager::Instance()->drawFrame("tower3",256 * 2,0,256,382,1, m_currentFrame, renderer);
    // render end
    SDL_RenderPresent(renderer);
}

void Game::update()
{
    m_currentFrame = int (((SDL_GetTicks() / m_animSpeed ) % 8));
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

