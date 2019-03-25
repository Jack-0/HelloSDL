//
// Created by jack on 25/03/19.
//

#ifndef HELLOSDL_INPUTHANDLER_H
#define HELLOSDL_INPUTHANDLER_H

#include <vector>
#include <SDL2/SDL.h>
#include "Game.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
            s_pInstance = new InputHandler();
    }

    void update();
    void clean();

    bool isKeyDown(SDL_Scancode key);

    bool getMouseButtonStates(int btnNumber){
        return m_mouseButtonStates[btnNumber];
    }

    Vector2D* getMousePosition(){
        return m_mousePosition;
    }

private:

    InputHandler();
    ~InputHandler() {}

    static InputHandler* s_pInstance;
    void handleMouse(const SDL_Event& event);

    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    const Uint8* m_keystates;

};

typedef InputHandler TheInputHandler;


#endif //HELLOSDL_INPUTHANDLER_H
