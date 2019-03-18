//
// Created by jack on 14/03/19.
//

#ifndef HELLOSDL_GAME_H
#define HELLOSDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:
    Game() {}
    ~Game() {}

    int m_currentFrame;
    int m_animSpeed;

    bool init(const char*, int, int, int, int, int);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning() { return running; }

private:

    GameObject* gameObject = nullptr;
    Player* player = nullptr;

    void draw(const char*, int, int, bool);
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;


};

#endif //HELLOSDL_GAME_H


