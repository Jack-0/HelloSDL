//
// Created by jack on 14/03/19.
//

#include <iostream>

#include "Game.h"
#include "entity/AnimatedGraphic.h"
#include "utilities/SoundManager.h"

Game* Game::s_pInstance = 0; // singleton


bool Game::init(const char* title, int x, int y, int width, int height, int flags)
{
    m_screenWidth = width;
    m_screenHeight = height;
    m_screenCenter = Vector2D(width / 2, height / 2);

    // initialise SDL
    if(SDL_INIT_EVERYTHING >= 0)
    {
        std::cout << "SDL initialisation successful" << std::endl;
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if(window != 0)
        {
            std::cout << "Window initialisation successful" << std::endl;
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer != 0)
            {
                std::cout << "Renderer initialisation successful" << std::endl;
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
            }
            else
                { return false; }
        } else
            { return false; }
    } else
        { return false; }


    TheGameObjectFactory::Instance()->registerType("MenuButton", new ButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    TheSoundManager::Instance()->load("../res/sound/bang.wav", "bang");
    TheSoundManager::Instance()->load("../res/sound/beep.wav", "beep");

    // Game state
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());




    // game is now running
    running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    /// render start
    m_pGameStateMachine->render();
    /// render end
    SDL_RenderPresent(renderer);
}

void Game::draw()
{
    // draw all game objects
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

/**
 * returns a random number in the range low - high
 * @param low is the lowest possible int
 * @param high is the highest possible int
 * @return random value between low and high
 */
int Game::getRandom(int low, int high)
{
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(low, high);
    return rand(rng);
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::clean()
{
    std::cout << "Cleaning game" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::quit()
{
    running = false;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}