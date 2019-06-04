//
// Created by jack on 14/03/19.
//

#ifndef HELLOSDL_GAME_H
#define HELLOSDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <random>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"


class Game
{
public:
    ~Game() {}

    /// Ensure game is a singleton
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

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    void menu();
    void quit();

    int getRandom(int low, int high);

    SDL_Renderer* getRenderer() const { return renderer; }

private:

    Game() {}

    static Game* s_pInstance;

    std::vector<GameObject*> m_gameObjects;

    void draw();
    void load(std::string name, std::string path);

    bool running;
    bool playerInit = false;

    SDL_Window* window;
    SDL_Renderer* renderer;

    std::random_device dev;

    enum game_states
    {
        MENU = 0,
        PLAY = 1,
        GAMEOVER = 2
    };

    int m_currentState = 0;

    GameStateMachine* m_pGameStateMachine;


};

typedef Game TheGame;

#endif //HELLOSDL_GAME_H


