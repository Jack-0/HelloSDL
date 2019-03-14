#include <iostream>
#include <SDL2/SDL.h>

SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

int main()
{
    if(SDL_INIT_EVERYTHING >= 0)
    {
        std::cout << "Hello";
        window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                640, 480, SDL_WINDOW_SHOWN);

        if(window != 0)
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
        }
    }
    else
        return -1;

    SDL_SetRenderDrawColor(renderer, 0, 100, 100, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_Quit();

    return 0;
}