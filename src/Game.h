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

    bool init(const char* title, int x, int y, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool isRunning() { return running; }
    void quit();

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
    SDL_Renderer* getRenderer() const { return renderer; }
    int getScreenWidth() { return m_screenWidth; }
    int getScreenHeight() { return m_screenHeight; }
    Vector2D getScreenCenter() { return m_screenCenter; }

private:

    Game() {}
    void draw();

    int m_screenWidth;
    int m_screenHeight;
    Vector2D m_screenCenter = Vector2D(0,0);


    static Game* s_pInstance;
    bool running;
    std::vector<GameObject*> m_gameObjects;
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameStateMachine* m_pGameStateMachine;

};

typedef Game TheGame;

#endif //HELLOSDL_GAME_H


