//
// Created by jack on 25/03/19.
//

#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0; // singleton


InputHandler::InputHandler()
{

    // set the three mouse button states to false
    for(int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
}

void InputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        // handle user clicking red cross (exit button in top bar)
        if(event.type == SDL_QUIT)
            TheGame::Instance()->quit();

        // handle mouse events
        handleMouse(event);
    }
}

void InputHandler::handleMouse(const SDL_Event& event)
{
    // handle mouse events
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = true;
        }
        if(event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = true;
        }
        if(event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[RIGHT] = true;
        }
    }

    if(event.type == SDL_MOUSEBUTTONUP)
    {
        if(event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = false;
        }
        if(event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = false;
        }
        if(event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[RIGHT] = false;
        }
    }
}