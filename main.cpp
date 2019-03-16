#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

Game* game = 0;

int main()
{
    game = new Game();

    game->init("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900, 0);

    while(game->isRunning())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}