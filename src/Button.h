//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_BUTTON_H
#define HELLOSDL_BUTTON_H

#include "SDLGameObject.h"
#include "InputHandler.h"

class Button : public SDLGameObject
{
public:

    Button(const LoaderParams* pParams, void (*callback) () );

    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    enum btn_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback) ();

    bool m_bReleased;

};


#endif //HELLOSDL_BUTTON_H
