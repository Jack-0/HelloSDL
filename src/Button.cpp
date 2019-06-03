//
// Created by jack on 31/05/19.
//

#include "Button.h"

Button::Button(const LoaderParams *pParams)
: SDLGameObject(pParams)
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
    /*
    if(pMousePos->getX() < (m_pos.getX() + m_width)
    && pMousePos->getX() > m_pos.getX()
    && pMousePos->getY() < (m_pos.getY() + m_height)
    && pMousePos->getY() > m_pos.getY() )
     */
    if(mx < (m_pos.getX() + m_width)
    && mx > m_pos.getX()
    && my < (m_pos.getY() + m_height)
    && my > m_pos.getY() )
    {
        m_currentFrame = MOUSE_OVER;

        if(TheInputHandler::Instance()->getMouseButtonStates(LEFT))
        {
            m_currentFrame = CLICKED;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}