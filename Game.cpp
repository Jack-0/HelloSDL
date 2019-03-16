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
    // render texture
    SDL_RenderClear(renderer);
    draw("/home/jack/CLionProjects/HelloSDL/res/test.png", 0, 0, false);
    draw("/home/jack/CLionProjects/HelloSDL/res/npc.png", 0, 300, true);
    draw("/home/jack/CLionProjects/HelloSDL/res/dice.png", 0,0, false);
    SDL_RenderPresent(renderer);
}

void Game::draw(const char * location, int x, int y, bool resize)
{
    SDL_Surface* tempSurface = IMG_Load(location);
    if(!tempSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        running = false;
        // handle error
    }


    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);



    SDL_Rect sourceRec;
    SDL_Rect destRec;

    SDL_QueryTexture(texture, NULL, NULL, &sourceRec.w, &sourceRec.h);


    destRec.x = sourceRec.x = x;
    destRec.y = sourceRec.y = y;


    destRec.h = sourceRec.h;
    destRec.w = sourceRec.w;

    if(resize)
    {
        destRec.h = 100;
        destRec.w = 100;
    }


    SDL_RenderCopy(renderer, texture, &sourceRec, & destRec);
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

