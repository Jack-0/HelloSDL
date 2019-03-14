//
// Created by jack on 14/03/19.
//

#include <iostream>
#include "Game.h"

bool Game::init(const char* title, int x, int y, int w, int h, int flags)
{
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


    running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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
                //std::cout << "Key \"" << event.type << "\" pressed..." << std::endl;
                break;
        }
    }
}

