//
// Created by jack on 25/03/19.
//

#ifndef HELLOSDL_INPUTHANDLER_H
#define HELLOSDL_INPUTHANDLER_H

#include <vector>
#include <SDL2/SDL.h>
#include "../Game.h"

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

        return s_pInstance;
    }

    void update();
    void clean();

    bool isKeyDown(SDL_Scancode key);

    bool getMouseButtonStates(int btnNumber){
        return m_mouseButtonStates[btnNumber];
    }

    float getMouseX()
    {
        return mouseX;
    }

    float getMouseY()
    {
        return mouseY;
    }

private:

    float mouseX;
    float mouseY;

    InputHandler();
    ~InputHandler() {}

    void onKeyDown();
    void onKeyUp();

    static InputHandler* s_pInstance;
    void handleMouse(const SDL_Event& event);

    std::vector<bool> m_mouseButtonStates;

    const Uint8* m_keystates = SDL_GetKeyboardState(NULL);

};

typedef InputHandler TheInputHandler;


#endif //HELLOSDL_INPUTHANDLER_H
