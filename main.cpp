#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include "Player.h"

SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

Game* game = nullptr;

int main()
{
    //game = new Game();
    if(TheGame::Instance()->init("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900, 0))
    {
        while(TheGame::Instance()->isRunning())
        {
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            SDL_Delay(10);
        }
    }
    else
    {
        return -1;
    }

    TheGame::Instance()->clean();

    return 0;
}