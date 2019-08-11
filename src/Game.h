//
// Created by jack on 14/03/19.
//

#ifndef HELLOSDL_GAME_H
#define HELLOSDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "graphics/TextureManager.h"
#include "entity/GameObject.h"
#include "entity/mob/Player.h"
#include "entity/mob/Enemy.h"
#include "input/Button.h"
#include "state/GameStateMachine.h"
#include "state/MainMenuState.h"
#include "state/PlayState.h"


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

    void quit();

    SDL_Renderer* getRenderer() const { return renderer; }

private:

    Game() {}
    void draw();

    static Game* s_pInstance;
    bool running;
    std::vector<GameObject*> m_gameObjects;
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif //HELLOSDL_GAME_H


