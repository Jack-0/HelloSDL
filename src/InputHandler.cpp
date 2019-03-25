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
        if(event.type == SDL_QUIT)
            TheGame::Instance()->quit();
    }
}