//
// Created by jack on 31/05/19.
//

#include "Button.h"

Button::Button(const LoaderParams *pParams, void (*callback) ())
: SDLGameObject(pParams), m_callback(callback)
{
}

void Button::draw()
{
    SDLGameObject::draw();
}

void Button::update()
{
    //Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
    float mx = TheInputHandler::Instance()->getMouseX();
    float my = TheInputHandler::Instance()->getMouseY();

    if(mx < (m_pos.getX() + m_width)
    && mx > m_pos.getX()
    && my < (m_pos.getY() + m_height)
    && my > m_pos.getY() )
    {
        if(TheInputHandler::Instance()->getMouseButtonStates(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            m_callback(); // call out call back function
            m_bReleased = false;
        }
        else if (!TheInputHandler::Instance()->getMouseButtonStates(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void Button::clean()
{
    SDLGameObject::clean();
}