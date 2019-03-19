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
    ~Game() {}

    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
    }

    bool init(const char*, int, int, int, int, int);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning() { return running; }

    SDL_Renderer* getRenderer() const { return renderer; }

private:

    Game() {}

    static Game* s_pInstance;

    //GameObject* gameObject = nullptr;
    //Player* player = nullptr;

    int m_currentFrame;
    int m_animSpeed;

    std::vector<SDLGameObject*> m_gameObjects;
    //GameObject* m_player;
    //GameObject* m_gameObject1;
    //GameObject* m_gameObject2;
    //GameObject* m_gameObject3;
    //GameObject* m_enemy;


    void draw();
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;


};

typedef Game TheGame;

#endif //HELLOSDL_GAME_H


