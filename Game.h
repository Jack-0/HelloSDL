//
// Created by jack on 14/03/19.
//

#ifndef HELLOSDL_GAME_H
#define HELLOSDL_GAME_H

#include <SDL2/SDL.h>

class Game
{
public:
    Game() {}
    ~Game() {}

    bool init(const char*, int, int, int, int, int);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning() { return running; }

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;


};

#endif //HELLOSDL_GAME_H


