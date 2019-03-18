//
// Created by jack on 14/03/19.
//

#ifndef HELLOSDL_GAME_H
#define HELLOSDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

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

    GameObject* gameObject = nullptr;
    Player* player = nullptr;

    int m_currentFrame;
    int m_animSpeed;

    std::vector<GameObject*> m_gameObjects;
    GameObject* m_player;
    GameObject* m_gameObject1;
    GameObject* m_gameObject2;
    GameObject* m_gameObject3;
    GameObject* m_enemy;


    void draw();
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;


};

#endif //HELLOSDL_GAME_H


